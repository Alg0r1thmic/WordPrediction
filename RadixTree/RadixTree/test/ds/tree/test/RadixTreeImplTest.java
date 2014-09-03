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

package ds.tree.test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

import org.junit.Before;
import org.junit.Test;

import ds.tree.DuplicateKeyException;
import ds.tree.RadixTree;
import ds.tree.RadixTreeImpl;

/**
 * Unit tests for {@link RadixTreeImpl}
 * 
 * @author Tahseen Ur Rehman (tahseen.ur.rehman {at.spam.me.not} gmail.com) 
 * @author Javid Jamae 
 * @
 */
public class RadixTreeImplTest {

	RadixTreeImpl<String> trie;
	RadixTreeImpl<String> unabrTrie;
	RadixTreeImpl<String> rogetTrie; 

	@Before
	public void createTree() {
		trie = new RadixTreeImpl<String>();
		unabrTrie = new RadixTreeImpl<String>();
		rogetTrie = new RadixTreeImpl<String>();
	}

	@Test
	public void testSearchForPartialParentAndLeafKeyWhenOverlapExists() {
		trie.insert("abcd", "abcd");
		trie.insert("abce", "abce");

		assertEquals(0, trie.searchPrefix("abe", 10).size());
		assertEquals(0, trie.searchPrefix("abd", 10).size());
	}

	@Test
	public void testSearchForLeafNodesWhenOverlapExists() {
		trie.insert("abcd", "abcd");
		trie.insert("abce", "abce");

		assertEquals(1, trie.searchPrefix("abcd", 10).size());
		assertEquals(1, trie.searchPrefix("abce", 10).size());
	}

	@Test
	public void testSearchForStringSmallerThanSharedParentWhenOverlapExists() {
		trie.insert("abcd", "abcd");
		trie.insert("abce", "abce");

		assertEquals(2, trie.searchPrefix("ab", 10).size());
		assertEquals(2, trie.searchPrefix("a", 10).size());
	}

	@Test
	public void testSearchForStringEqualToSharedParentWhenOverlapExists() {
		trie.insert("abcd", "abcd");
		trie.insert("abce", "abce");

		assertEquals(2, trie.searchPrefix("abc", 10).size());
	}

	@Test
	public void testInsert() {
		trie.insert("apple", "apple");
		trie.insert("bat", "bat");
		trie.insert("ape", "ape");
		trie.insert("bath", "bath");
		trie.insert("banana", "banana"); 

		assertEquals(trie.find("apple"), "apple");
		assertEquals(trie.find("bat"), "bat");
		assertEquals(trie.find("ape"), "ape");
		assertEquals(trie.find("bath"), "bath");
		assertEquals(trie.find("banana"), "banana");
	}

	@Test
	public void testInsertExistingUnrealNodeConvertsItToReal() {
		trie.insert("applepie", "applepie");
		trie.insert("applecrisp", "applecrisp");

		assertFalse(trie.contains("apple"));

		trie.insert("apple", "apple");

		assertTrue(trie.contains("apple"));
	}

	@Test
	public void testDuplicatesNotAllowed() {
		RadixTreeImpl<String> trie = new RadixTreeImpl<String>();

		trie.insert("apple", "apple");

		try {
			trie.insert("apple", "apple2");
			fail("Duplicate should not have been allowed");
		} catch (DuplicateKeyException e) {
			assertEquals("Duplicate key: 'apple'", e.getMessage());
		}
	}

	@Test
	public void testInsertWithRepeatingPatternsInKey() {
		trie.insert("xbox 360", "xbox 360");
		trie.insert("xbox", "xbox");
		trie.insert("xbox 360 games", "xbox 360 games");
		trie.insert("xbox games", "xbox games");
		trie.insert("xbox xbox 360", "xbox xbox 360");
		trie.insert("xbox xbox", "xbox xbox");
		trie.insert("xbox 360 xbox games", "xbox 360 xbox games");
		trie.insert("xbox games 360", "xbox games 360");
		trie.insert("xbox 360 360", "xbox 360 360");
		trie.insert("xbox 360 xbox 360", "xbox 360 xbox 360");
		trie.insert("360 xbox games 360", "360 xbox games 360");
		trie.insert("xbox xbox 361", "xbox xbox 361");

		assertEquals(12, trie.getSize());
	}

	@Test
	public void testDeleteNodeWithNoChildren() {
		RadixTreeImpl<String> trie = new RadixTreeImpl<String>();
		trie.insert("apple", "apple");
		assertTrue(trie.delete("apple"));
	}

	@Test
	public void testDeleteNodeWithOneChild() {
		RadixTreeImpl<String> trie = new RadixTreeImpl<String>();
		trie.insert("apple", "apple");
		trie.insert("applepie", "applepie");
		assertTrue(trie.delete("apple"));
		assertTrue(trie.contains("applepie"));
		assertFalse(trie.contains("apple"));
	}

	@Test
	public void testDeleteNodeWithMultipleChildren() {
		RadixTreeImpl<String> trie = new RadixTreeImpl<String>();
		trie.insert("apple", "apple");
		trie.insert("applepie", "applepie");
		trie.insert("applecrisp", "applecrisp");
		assertTrue(trie.delete("apple"));
		assertTrue(trie.contains("applepie"));
		assertTrue(trie.contains("applecrisp"));
		assertFalse(trie.contains("apple"));
	}

	@Test
	public void testCantDeleteSomethingThatDoesntExist() {
		RadixTreeImpl<String> trie = new RadixTreeImpl<String>();
		assertFalse(trie.delete("apple"));
	}

	@Test
	public void testCantDeleteSomethingThatWasAlreadyDeleted() {
		RadixTreeImpl<String> trie = new RadixTreeImpl<String>();
		trie.insert("apple", "apple");
		trie.delete("apple");
		assertFalse(trie.delete("apple"));
	}

	@Test
	public void testChildrenNotAffectedWhenOneIsDeleted() {
		RadixTreeImpl<String> trie = new RadixTreeImpl<String>();
		trie.insert("apple", "apple");
		trie.insert("appleshack", "appleshack");
		trie.insert("applepie", "applepie");
		trie.insert("ape", "ape");

		trie.delete("apple");

		assertTrue(trie.contains("appleshack"));
		assertTrue(trie.contains("applepie"));
		assertTrue(trie.contains("ape"));
		assertFalse(trie.contains("apple"));
	}

	@Test
	public void testSiblingsNotAffectedWhenOneIsDeleted() {
		RadixTreeImpl<String> trie = new RadixTreeImpl<String>();
		trie.insert("apple", "apple");
		trie.insert("ball", "ball");

		trie.delete("apple");

		assertTrue(trie.contains("ball"));
	}

	@Test
	public void testCantDeleteUnrealNode() {
		RadixTreeImpl<String> trie = new RadixTreeImpl<String>();
		trie.insert("apple", "apple");
		trie.insert("ape", "ape");

		assertFalse(trie.delete("ap"));
	}


	@Test
	public void testCantFindRootNode() {
		assertNull(trie.find(""));
	}

	@Test
	public void testFindSimpleInsert() {
		trie.insert("apple", "apple");
		assertNotNull(trie.find("apple"));
	}

	@Test
	public void testContainsSimpleInsert() {
		trie.insert("apple", "apple");
		assertTrue(trie.contains("apple"));
	}

	@Test
	public void testFindChildInsert() {
		trie.insert("apple", "apple");
		trie.insert("ape", "ape");
		trie.insert("appletree", "appletree");
		trie.insert("appleshackcream", "appleshackcream");
		assertNotNull(trie.find("appletree"));
		assertNotNull(trie.find("appleshackcream"));
		assertNotNull(trie.contains("ape"));
	}

	@Test
	public void testContainsChildInsert() {
		trie.insert("apple", "apple");
		trie.insert("ape", "ape");
		trie.insert("appletree", "appletree");
		trie.insert("appleshackcream", "appleshackcream");
		assertTrue(trie.contains("appletree"));
		assertTrue(trie.contains("appleshackcream"));
		assertTrue(trie.contains("ape"));
	}

	@Test
	public void testCantFindNonexistantNode() {
		assertNull(trie.find("apple"));
	}

	@Test
	public void testDoesntContainNonexistantNode() {
		assertFalse(trie.contains("apple"));
	}

	@Test
	public void testCantFindUnrealNode() {
		trie.insert("apple", "apple");
		trie.insert("ape", "ape");
		assertNull(trie.find("ap"));
	}

	@Test
	public void testDoesntContainUnrealNode() {
		trie.insert("apple", "apple");
		trie.insert("ape", "ape");
		assertFalse(trie.contains("ap"));
	}


	@Test
	public void testSearchPrefix_LimitGreaterThanPossibleResults() {
		trie.insert("apple", "apple");
		trie.insert("appleshack", "appleshack");
		trie.insert("appleshackcream", "appleshackcream");
		trie.insert("applepie", "applepie");
		trie.insert("ape", "ape");

		ArrayList<String> result = trie.searchPrefix("app", 10);
		assertEquals(4, result.size());

		assertTrue(result.contains("appleshack"));
		assertTrue(result.contains("appleshackcream"));
		assertTrue(result.contains("applepie"));
		assertTrue(result.contains("apple"));
	}

	@Test
	public void testSearchPrefix_LimitLessThanPossibleResults() {
		trie.insert("apple", "apple");
		trie.insert("appleshack", "appleshack");
		trie.insert("appleshackcream", "appleshackcream");
		trie.insert("applepie", "applepie");
		trie.insert("ape", "ape");

		ArrayList<String> result = trie.searchPrefix("appl", 3);
		assertEquals(3, result.size());

		assertTrue(result.contains("appleshack"));
		assertTrue(result.contains("applepie"));
		assertTrue(result.contains("apple"));
	}

	@Test
	public void testGetSize() {
		trie.insert("apple", "apple");
		trie.insert("appleshack", "appleshack");
		trie.insert("appleshackcream", "appleshackcream");
		trie.insert("applepie", "applepie");
		trie.insert("ape", "ape");

		assertTrue(trie.getSize() == 5);
	}

	@Test
	public void testDeleteReducesSize() {
		trie.insert("apple", "apple");
		trie.insert("appleshack", "appleshack");

		trie.delete("appleshack");

		assertTrue(trie.getSize() == 1);
	}    

	@Test
	public void testComplete() {
		// create a new Trie
		RadixTree<String> trie = new RadixTreeImpl<String>();

		trie.insert("apple", "apple");
		trie.insert("appleshack", "appleshack");
		trie.insert("applepie", "applepie");
		trie.insert("applegold", "applegold");
		trie.insert("applegood", "applegood");

		assertEquals("", trie.complete("z"));
		assertEquals("apple", trie.complete("a"));
		assertEquals("apple", trie.complete("app"));
		assertEquals("appleshack", trie.complete("apples"));
		assertEquals("applego", trie.complete("appleg"));
	}
	


	@Test
	public void compileRogetDictionary(){
		rogetTrie = new RadixTreeImpl<String>();

		InputStream in = getClass().getResourceAsStream("../roget-dictionary.txt");
		BufferedReader reader = new BufferedReader(new InputStreamReader(in));

		String read = null;
		try {
			while( (read = reader.readLine()) != null) {
				StringTokenizer st = new StringTokenizer(read);
				while(st.hasMoreTokens()) {
					String token = st.nextToken();
					rogetTrie.insert(token, token);
				}
			}

			System.out.println("Size: " + rogetTrie.getSize() + " " + (rogetTrie.getBytes().length / 1024) + "KB");
			

			ArrayList<String> prefix = rogetTrie.searchPrefix("sub", 17474);
			
			System.out.println(prefix.size());
			for(String s : prefix){
				System.out.println(s);
			}
		} catch (DuplicateKeyException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Test
	public void compileUnabridgedDictionary(){
//		unabrTrie = new RadixTreeImpl<String>();

		InputStream in = getClass().getResourceAsStream("../unabridged-dictionary.txt");
		BufferedReader reader = new BufferedReader(new InputStreamReader(in));

		String read = null;
		try {
			while( (read = reader.readLine()) != null) {
				StringTokenizer st = new StringTokenizer(read);
				while(st.hasMoreTokens()) {
					String token = st.nextToken();
					unabrTrie.insert(token, token);
				}
			}
		} catch (DuplicateKeyException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Test 
	public void testRogetDictionary(){
		RadixTree<String> trie = new RadixTreeImpl<String>();

		InputStream in = getClass().getResourceAsStream("../roget-dictionary.txt");
		BufferedReader reader = new BufferedReader(new InputStreamReader(in));

		try {
			String read = null;
			while( (read = reader.readLine()) != null) {
				StringTokenizer st = new StringTokenizer(read);
				while(st.hasMoreTokens()) {
					String token = st.nextToken();
					trie.insert(token, token);
				}
			}

			System.out.println("Size: " + trie.getSize() + " " + (trie.getBytes().length / 1024) + "KB");


			String tree = trie.printTree();
			File file = new File("../RadixTree1.txt");
			if(file.exists()){
				file.delete();
			}
			file.createNewFile();
			FileOutputStream out = new FileOutputStream(file);
			byte[] contents = tree.getBytes();
			out.write(contents);
			out.flush();
			out.close();


		} catch (DuplicateKeyException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	@Test 
	public void testUnabridgedDictionary(){
		RadixTree<String> trie = new RadixTreeImpl<String>();

		InputStream in = getClass().getResourceAsStream("../unabridged-dictionary.txt");
		BufferedReader reader = new BufferedReader(new InputStreamReader(in));

		try {
			String read = null;
			while( (read = reader.readLine()) != null) {
				StringTokenizer st = new StringTokenizer(read);
				while(st.hasMoreTokens()) {
					String token = st.nextToken();
					trie.insert(token, token);
				}
			}

			System.out.println("Size: " + trie.getSize() + " " + (trie.getBytes().length / 1024) + "KB");


			String tree = trie.printTree();
			File file = new File("../RadixTree1.txt");
			if(file.exists()){
				file.delete();
			}
			file.createNewFile();
			FileOutputStream out = new FileOutputStream(file);
			byte[] contents = tree.getBytes();
			out.write(contents);
			out.flush();
			out.close();


		} catch (DuplicateKeyException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Test 
	public void rogetFind(){
		rogetTrie.find("sabbatarianism");
	}

	@Test 
	public void unabridgedFind(){
		unabrTrie.find("sabbatarianism");
	}
}
