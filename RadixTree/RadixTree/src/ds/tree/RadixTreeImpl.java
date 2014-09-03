/*
The MIT License

Copyright (c) 2008 Tahseen Ur Rehman, Javid Jamae

http://code.google.com/p/radixtree/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

package ds.tree;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutput;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Formattable;
import java.util.Formatter;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/**
 * Implementation for Radix tree {@link RadixTree}
 * 
 * @author Tahseen Ur Rehman (tahseen.ur.rehman {at.spam.me.not} gmail.com)
 * @author Javid Jamae 
 * @author Dennis Heidsiek
 */
public class RadixTreeImpl<T> implements RadixTree<T>, Formattable, Serializable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 6843530899759718171L;

	protected RadixTreeNode<T> root;

	protected long size;

	/**
	 * Create a Radix Tree with only the default node root.
	 */
	public RadixTreeImpl() {
		root = new RadixTreeNode<T>();
		root.setKey("");
		size = 0;
	}

	public T find(String key) {
		Visitor<T,T> visitor = new VisitorImpl<T,T>() {

			/**
			 * 
			 */
			private static final long serialVersionUID = 883289395658095952L;

			public void visit(String key, RadixTreeNode<T> parent,
					RadixTreeNode<T> node) {
				if (node.isReal()) 
					result = node.getValue();
			}
		};

		visit(key, visitor);

		return visitor.getResult();
	}

	public boolean delete(String key) {
		Visitor<T, Boolean> visitor = new VisitorImpl<T, Boolean>(Boolean.FALSE) {
			/**
			 * 
			 */
			private static final long serialVersionUID = 6346426140781431693L;

			public void visit(String key, RadixTreeNode<T> parent,
					RadixTreeNode<T> node) {
				result = node.isReal();

				// if it is a real node
				if (result) {
					// If there no children of the node we need to
					// delete it from the its parent children list
					if (node.getChildern().size() == 0) {
						Iterator<RadixTreeNode<T>> it = parent.getChildern()
								.iterator();
						while (it.hasNext()) {
							if (it.next().getKey().equals(node.getKey())) {
								it.remove();
								break;
							}
						}

						// if parent is not real node and has only one child
						// then they need to be merged.
						if (parent.getChildern().size() == 1
								&& parent.isReal() == false) {
							mergeNodes(parent, parent.getChildern().get(0));
						}
					} else if (node.getChildern().size() == 1) {
						// we need to merge the only child of this node with
						// itself
						mergeNodes(node, node.getChildern().get(0));
					} else { // we just need to mark the node as non real.
						node.setReal(false);
					}
				}
			}

			/**
			 * Merge a child into its parent node. Operation only valid if it is
			 * only child of the parent node and parent node is not a real node.
			 * 
			 * @param parent
			 *            The parent Node
			 * @param child
			 *            The child Node
			 */
			protected void mergeNodes(RadixTreeNode<T> parent,
					RadixTreeNode<T> child) {
				parent.setKey(parent.getKey() + child.getKey());
				parent.setReal(child.isReal());
				parent.setValue(child.getValue());
				parent.setChildern(child.getChildern());
			}

		};

		visit(key, visitor);

		if(visitor.getResult()) {
			size--;
		}
		return visitor.getResult().booleanValue();
	}

	/*
	 * (non-Javadoc)
	 * @see ds.tree.RadixTree#insert(java.lang.String, java.lang.Object)
	 */
	public void insert(String key, T value) throws DuplicateKeyException {
		try {
			insert(key, root, value);
		} catch (DuplicateKeyException e) {
			// re-throw the exception with 'key' in the message
			//throw new DuplicateKeyException("Duplicate key: '" + key + "'");
		}
		size++;
	}

	/**
	 * Recursively insert the key in the radix tree.
	 * 
	 * @param key The key to be inserted
	 * @param node The current node
	 * @param value The value associated with the key 
	 * @throws DuplicateKeyException If the key already exists in the database.
	 */
	protected void insert(String key, RadixTreeNode<T> node, T value)
			throws DuplicateKeyException {

		int numberOfMatchingCharacters = node.getNumberOfMatchingCharacters(key);

		// we are either at the root node
		// or we need to go down the tree
		if (node.getKey().equals("") == true || numberOfMatchingCharacters == 0 || (numberOfMatchingCharacters < key.length() && numberOfMatchingCharacters >= node.getKey().length())) {
			boolean flag = false;
			String newText = key.substring(numberOfMatchingCharacters, key.length());
			for (RadixTreeNode<T> child : node.getChildern()) {
				if (child.getKey().startsWith(newText.charAt(0) + "")) {
					flag = true;
					insert(newText, child, value); //It still matches, continue down the tree but ignore the nodes we've already passed through
					break;
				}
			}
			//We will only get here if there was no match to any children
			// just add the node as the child of the current node
			if (flag == false) {
				RadixTreeNode<T> n = new RadixTreeNode<T>();
				n.setKey(newText);
				n.setReal(true);
				n.setValue(value);

				node.getChildern().add(n);
			}
		}
		// there is a exact match just make the current node as data node
		else if (numberOfMatchingCharacters == key.length() && numberOfMatchingCharacters == node.getKey().length()) {
			if (node.isReal() == true) {
				throw new DuplicateKeyException("Duplicate key");
			}

			node.setReal(true);
			node.setValue(value);
		}
		// This node need to be split as the key to be inserted
		// is a prefix of the current node key
		else if (numberOfMatchingCharacters > 0 && numberOfMatchingCharacters < node.getKey().length()) {
			RadixTreeNode<T> n1 = new RadixTreeNode<T>();
			n1.setKey(node.getKey().substring(numberOfMatchingCharacters, node.getKey().length()));
			n1.setReal(node.isReal());
			n1.setValue(node.getValue());
			n1.setChildern(node.getChildern());

			node.setKey(key.substring(0, numberOfMatchingCharacters));
			node.setReal(false);
			node.setChildern(new ArrayList<RadixTreeNode<T>>());
			node.getChildern().add(n1);

			if(numberOfMatchingCharacters < key.length()) {
				RadixTreeNode<T> n2 = new RadixTreeNode<T>();
				n2.setKey(key.substring(numberOfMatchingCharacters, key.length()));
				n2.setReal(true);
				n2.setValue(value);

				node.getChildern().add(n2);
			} else {
				node.setValue(value);
				node.setReal(true);
			}
		}        
		// this key need to be added as the child of the current node
		else {
			RadixTreeNode<T> n = new RadixTreeNode<T>();
			n.setKey(node.getKey().substring(numberOfMatchingCharacters, node.getKey().length()));
			n.setChildern(node.getChildern());
			n.setReal(node.isReal());
			n.setValue(node.getValue());

			node.setKey(key);
			node.setReal(true);
			node.setValue(value);

			node.getChildern().add(n);
		}
	}

	public ArrayList<T> searchPrefix(String key, int recordLimit) {
		ArrayList<T> keys = new ArrayList<T>();

		RadixTreeNode<T> node = searchPrefix(key, root);

		if (node != null) {
			if (node.isReal()) {
				keys.add(node.getValue());
			}
			getNodes(node, keys, recordLimit);
		}

		return keys;
	}

	protected void getNodes(RadixTreeNode<T> parent, ArrayList<T> keys, int limit) {
		Queue<RadixTreeNode<T>> queue = new LinkedList<RadixTreeNode<T>>();

		queue.addAll(parent.getChildern());

		while (!queue.isEmpty()) {
			RadixTreeNode<T> node = queue.remove();
			if (node.isReal() == true) {
				keys.add(node.getValue());
			}

			if (keys.size() == limit) {
				break;
			}

			queue.addAll(node.getChildern());
		}
	}

	protected RadixTreeNode<T> searchPrefix(String key, RadixTreeNode<T> node) {
		RadixTreeNode<T> result = null;

		int numberOfMatchingCharacters = node.getNumberOfMatchingCharacters(key);

		if (numberOfMatchingCharacters == key.length() && numberOfMatchingCharacters <= node.getKey().length()) {
			result = node;
		} else if (node.getKey().equals("") == true
				|| (numberOfMatchingCharacters < key.length() && numberOfMatchingCharacters >= node.getKey().length())) {
			String newText = key.substring(numberOfMatchingCharacters, key.length());
			for (RadixTreeNode<T> child : node.getChildern()) {
				if (child.getKey().startsWith(newText.charAt(0) + "")) {
					result = searchPrefix(newText, child);
					break;
				}
			}
		}

		return result;
	}
	
	public int count_within_distance(String key, int distance, int marca) {
		return count_within_distance(key, root, 0, distance, marca);
	}
	
	/* Returns the number of words within distance k from key
	 * @ key: the key
	 * @ node: the current explored node
	 * @ i: position inside the node. In case the node has a key longer than a single character, indicates at which
	 * character are we.
	 * @k: the distance
	 */
	protected int count_within_distance(String key, RadixTreeNode<T> node, int i, int k, int marca) {
		int res = 0;
		//debug
		/*if (node.isReal() && node.getValue().equals("auvernias")) {
			System.out.println("auvernias NODE: " + key + " " + i +  " " + node.getKey().substring(i) + " " + k + " " + distance(node.getKey().substring(i),key));
		}
		if (node.getKey().substring(i).equals("nia") && key.equals("vios") && k == 2) {
			System.out.println("PATH seguit!: "+ k);
		}*/
		//fi debug
		if (k < 0) return 0;
		if (node.isReal() && !node.isMarked(marca)) {
			if (distance(node.getKey().substring(i),key) <= k) {
				res++;
				node.setMark(marca);
				//System.out.println(node.getValue());
			}
		}		
		if (node.getKey().isEmpty()) {//first level, the root level
			Iterator<RadixTreeNode<T>> it = node.getChildern().iterator();
			while (it.hasNext()) {
				RadixTreeNode<T> child = it.next();
				res += count_within_distance(key, child, 0, k, marca);
			}
		}
		else if (i == node.getKey().length()-1) {
			char c;
			if (!key.isEmpty()) c = key.charAt(0);
			else c = 'x'; //anything
			Iterator<RadixTreeNode<T>> it = node.getChildern().iterator();
			while (it.hasNext()) {
				RadixTreeNode<T> child = it.next();
				if (!key.isEmpty() && node.getKey().charAt(i) == c) {
					res += count_within_distance(key.substring(1), child, 0, k, marca); //the first letter coincides, follow the path
				}
				if (!key.isEmpty() && node.getKey().charAt(i) != c) {
					res += count_within_distance(key.substring(1), child, 0, k-1, marca); //substitution
				}
				res += count_within_distance(key, child, 0, k-1, marca); //insertion
			}
			if (!key.isEmpty()) res += count_within_distance(key.substring(1), node, i, k-1, marca); //deletion			
		}
		else if (node.getChildern().size() > 0) {//if there are no further leaves we just finished in a leave and so we already calculated in if (node.isReal())
			char c;
			if (!key.isEmpty()) c = key.charAt(0);
			else c = 'X'; //anything
			if (!key.isEmpty() && node.getKey().charAt(i) == c) {
				res += count_within_distance(key.substring(1), node, i+1, k, marca); //the first letter coincides, follow the path
			}
			if (!key.isEmpty() && node.getKey().charAt(i) != c) {
				res += count_within_distance(key.substring(1), node, i+1, k-1, marca); //substitution
			}
			res += count_within_distance(key, node, i+1, k-1, marca); //insertion
			
			if (!key.isEmpty()) res += count_within_distance(key.substring(1), node, i, k-1, marca); //deletion
		}
		return res;
	}
	
	/*
	 * Returns the Levenshtein distance between two strings
	 */
	private int distance(String a, String b) {
		int m[][] = new int[a.length()+1][b.length()+1];
		int cost;
		m[0][0] = 0;
		for (int i=1; i<=a.length(); i++) m[i][0] = i;
		for (int j=1; j<=b.length(); j++) m[0][j] = j;
		for (int i=1; i<=a.length(); i++)
			for (int j=1; j<=b.length(); j++) {
				if (a.charAt(i-1) == b.charAt(j-1)) cost = 0;
				else cost = 1;
			
				m[i][j] = minim(m[i-1][j-1]+cost,m[i-1][j]+1,m[i][j-1]+1); //substitution, deletion and insertion		
			}
		return m[a.length()][b.length()];
	}
	
	int min(int a, int b) {
		if (a<b) return a;
		return b;
	}
	
	private int minim(int a, int b, int c) {
		return min(min(a,b),min(a,c));
	}

	public boolean contains(String key) {
		Visitor<T, Boolean> visitor = new VisitorImpl<T,Boolean>(Boolean.FALSE) {
			/**
			 * 
			 */
			private static final long serialVersionUID = 2349063461240687376L;

			public void visit(String key, RadixTreeNode<T> parent,
					RadixTreeNode<T> node) {
				result = node.isReal();
			}
		};

		visit(key, visitor);

		return visitor.getResult().booleanValue();
	}

	/**
	 * visit the node those key matches the given key
	 * @param key The key that need to be visited
	 * @param visitor The visitor object
	 */
	public <R> void visit(String key, Visitor<T, R> visitor) {
		if (root != null) {
			visit(key, visitor, null, root);
		}
	}

	/**
	 * recursively visit the tree based on the supplied "key". calls the Visitor
	 * for the node those key matches the given prefix
	 * 
	 * @param prefix
	 *            The key o prefix to search in the tree
	 * @param visitor
	 *            The Visitor that will be called if a node with "key" as its
	 *            key is found
	 * @param node
	 *            The Node from where onward to search
	 */
	protected <R> void visit(String prefix, Visitor<T, R> visitor,
			RadixTreeNode<T> parent, RadixTreeNode<T> node) {

		int numberOfMatchingCharacters = node.getNumberOfMatchingCharacters(prefix);

		// if the node key and prefix match, we found a match!
		if (numberOfMatchingCharacters == prefix.length() && numberOfMatchingCharacters == node.getKey().length()) {
			visitor.visit(prefix, parent, node);
		} else if (node.getKey().equals("") == true // either we are at the
				// root
				|| (numberOfMatchingCharacters < prefix.length() && numberOfMatchingCharacters >= node.getKey().length())) { // OR we need to
			// traverse the childern
			String newText = prefix.substring(numberOfMatchingCharacters, prefix.length());
			for (RadixTreeNode<T> child : node.getChildern()) {
				// recursively search the child nodes
				if (child.getKey().startsWith(newText.charAt(0) + "")) {
					visit(newText, visitor, node, child);
					break;
				}
			}
		}
	}

	public long getSize() {
		return size;
	}

	/**
	 * Display the Trie on console.
	 * 
	 * WARNING! Do not use this for a large Trie, it's for testing purpose only.
	 * @see formatTo
	 */
	@Deprecated
	public void display() {
		formatNodeTo(new Formatter(System.out), 0, root);
	}

	@Deprecated
	protected void display(int level, RadixTreeNode<T> node) {
		formatNodeTo(new Formatter(System.out), level, node);
	}

	/**
	 * WARNING! Do not use this for a large Trie, it's for testing purpose only.
	 */
	protected void formatNodeTo(Formatter f, int level, RadixTreeNode<T> node) {
		for (int i = 0; i < level; i++) {
			f.format(" ");
		}
		f.format("|");
		for (int i = 0; i < level; i++) {
			f.format("-");
		}

		if (node.isReal() == true)
			f.format("%s[%s]*%n", node.getKey(),  node.getValue());
		else
			f.format("%s%n", node.getKey());

		for (RadixTreeNode<T> child : node.getChildern()) {
			formatNodeTo(f, level + 1, child);
		}		
	}

	/**
	 * Writes a textual representation of this tree to the given formatter.
	 * 
	 * Currently, all options are simply ignored.
	 * 
	 * WARNING! Do not use this for a large Trie, it's for testing purpose only.
	 */
	public void formatTo(Formatter formatter, int flags, int width, int precision) {
		formatNodeTo(formatter, 0, root);	
	}

	/**
	 * Complete the a prefix to the point where ambiguity starts.
	 * 
	 *  Example:
	 *  If a tree contain "blah1", "blah2"
	 *  complete("b") -> return "blah"
	 * 
	 * @param prefix The prefix we want to complete
	 * @return The unambiguous completion of the string.
	 */
	public String complete(String prefix) {
		return complete(prefix, root, "");
	}    

	protected String complete(String key, RadixTreeNode<T> node, String base) {
		int i = 0;
		int keylen = key.length();
		int nodelen = node.getKey().length();

		while (i < keylen && i < nodelen) {
			if (key.charAt(i) != node.getKey().charAt(i)) {
				break;
			}
			i++;
		}

		if (i == keylen && i <= nodelen) {
			return base + node.getKey();
		}
		else if (nodelen == 0 || (i < keylen && i >= nodelen)) {
			String beginning = key.substring(0, i);
			String ending = key.substring(i, keylen);
			for (RadixTreeNode<T> child : node.getChildern()) {
				if (child.getKey().startsWith(ending.charAt(0) + "")) {
					return complete(ending, child, base + beginning);
				}
			}
		}

		return "";
	}

	/**
	 * Returns this tree in bytes
	 */
	public byte[] getBytes(){
		byte[] data = new byte[]{0};
		try {
			ByteArrayOutputStream bos = new ByteArrayOutputStream(); 
			ObjectOutputStream oos = new ObjectOutputStream(bos);
			root.writeTreeToStream(oos);
			oos.flush(); 
			oos.close(); 
			bos.close();
			data = bos.toByteArray();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		return data;
	}
	
	/**
	 * Prints this tree 
	 */
	public String printTree(){
		return root.printNode("", 0, root.getKey());
	}

}