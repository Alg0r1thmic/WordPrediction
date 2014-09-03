/*
The MIT License

Copyright (c) 2008 Tahseen Ur Rehman

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

import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectInputStream;
import java.io.ObjectOutput;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * Represents a node of a Radix tree {@link RadixTreeImpl}
 * 
 * @author Tahseen Ur Rehman
 * @email tahseen.ur.rehman {at.spam.me.not} gmail.com
 * @param <T>
 */
public class RadixTreeNode<T> implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = -1222466631332766878L;

	/**
	 * Only contains the next letter that is different from it's parent's prefix. 
	 * Example if this key's value is backwards, and it's parent is back, 
	 * 		it's parent's key will be k, and this key will be w, representing "backw"
	 */
	private String key;

	private List<RadixTreeNode<T>> childern;

	private boolean real;

	private T value;
	
	private boolean visited;
	
	private int mark; //in online quering it tells us if the word has already been found.

	/**
	 * intailize the fields with default values to avoid null reference checks
	 * all over the places
	 */
	public RadixTreeNode() {
		key = "";
		childern = new ArrayList<RadixTreeNode<T>>();
		real = false;
		visited = false;
		mark = -1;
	}
	
	public RadixTreeNode(String key, T value, boolean real, List<RadixTreeNode<T>> list){
		this.key = (key == null ? "" : key);
		this.value = value;
		this.real = real;
		this.childern = (list == null ? new ArrayList<RadixTreeNode<T>>() : list);
		this.visited = false;
		this.mark = -1;
	}
	
	public RadixTreeNode(String key, T value, boolean real){
		this(key, value, real, new ArrayList<RadixTreeNode<T>>());
	}

	public T getValue() {
		return value;
	}

	public void setValue(T data) {
		this.value = data;
	}

	public String getKey() {
		return key;
	}

	public void setKey(String value) {
		this.key = value;
	}

	public boolean isReal() {
		return real;
	}
	
	public boolean isVisited() {
		return visited;
	}
	
	public boolean isMarked(int marca) {
		return mark == marca;
	}

	public void setReal(boolean datanode) {
		this.real = datanode;
	}
	
	public void setVisited(boolean b) {
		this.visited = b;
	}
	
	public void setMark(int marca) {
		mark = marca;
	}

	public List<RadixTreeNode<T>> getChildern() {
		return childern;
	}

	public void setChildern(List<RadixTreeNode<T>> childern) {
		this.childern = childern;
	}


	public int getNumberOfMatchingCharacters(String key) {
		int numberOfMatchingCharacters = 0;
		while (numberOfMatchingCharacters < key.length() && numberOfMatchingCharacters < this.getKey().length()) {
			if (key.charAt(numberOfMatchingCharacters) != this.getKey().charAt(numberOfMatchingCharacters)) {
				break;
			}
			numberOfMatchingCharacters++;
		}
		return numberOfMatchingCharacters;
	}
	
	public void addChild(RadixTreeNode<T> child){
		childern.add(child);
	}
	
	/**
	 * Writes this node and all child nodes to oos
	 * 
	 * @author KirstenCrear
	 * @param oos ObjectOutputStream to write to
	 * @throws IOException 
	 */
	public void writeTreeToStream(ObjectOutputStream oos) throws IOException{
		oos.writeObject(key);
		oos.writeObject(value);
		oos.writeObject(real);
		for(RadixTreeNode<T> child : childern){
			child.writeTreeToStream(oos);
		}
	}
	
	/**
	 * @author KirstenCrear
	 * @param tree 		Complete tree thus far
	 * @param depth		current depth
	 * @param key		current key
	 * @return string of child tree
	 */
	public String printNode(String tree, int depth, String key){
		StringBuffer buffer = new StringBuffer(tree);
		
		key += this.key;
		
		if(real)
			buffer.append(getTabs(depth) + key + " " + value + "\n");
		else 
			buffer.append(getTabs(depth) + this.key + "*" + "\n");
		
		
		depth++;
		for(RadixTreeNode<T> child : childern){
			buffer.append(child.printNode(tree, depth, key));
		}
		
		
		return buffer.toString(); 
	}

	/**
	 * @author KirstenCrear
	 * @param tabs
	 * @return string of tabs equal to the depth of this node for the purpose of printing the tree. 
	 */
	private String getTabs(int tabs){
		String tab = "";
		for(int i = 0; i < tabs; i++){
			tab += "\t";
		}
		return tab;
	}
	
	@Override
	public String toString() {
		return key;

	}
	
	public void writeTree(ObjectOutputStream oos) throws IOException{
		oos.writeUTF(key);
		oos.writeObject(value);
		oos.writeBoolean(real);
		oos.writeInt(childern.size());
		for(RadixTreeNode<T> child : childern){
			child.writeTree(oos);
		}
		oos.reset();
	}
	
	public void read(ObjectInputStream ois) throws IOException, ClassNotFoundException{
		int size = ois.readInt();
		
		for(int i = 0; i < size; i++){
			RadixTreeNode<T> child = readChild(ois);
			addChild(child);
			child.read(ois);
		}
		
	}
	
	@SuppressWarnings("unchecked")
	private RadixTreeNode<T> readChild(ObjectInputStream ois) throws IOException, ClassNotFoundException{
		return new RadixTreeNode<T>(ois.readUTF(), (T) ois.readObject(), ois.readBoolean());
	}
}
