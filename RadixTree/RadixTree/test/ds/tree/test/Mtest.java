package ds.tree.test;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.ListIterator;
import java.util.Scanner;

import ds.tree.*;

public class Mtest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		final long startTime = System.currentTimeMillis();
		final String dataFile = "/home/mmayo/code/BK-tree/words-lemas_processed_random.txt";
		final String queryFile = "/home/mmayo/code/learning_words/sets/all_words_unique.txt";
		RadixTreeImpl<String> rt = new RadixTreeImpl<String>();
		try {
			readInput(rt,dataFile);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		final long endBuild = System.currentTimeMillis();
		
		try {
			processQueries(rt, queryFile,0);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//System.out.println(rt.count_within_distance("hola", 2, 0));
		/*
		rt.insert("hola","hola");
		rt.insert("adeu","adeu");
		rt.insert("mama","mama");
		rt.insert("ala", "ala");
		rt.insert("aleta", "aleta");
		rt.insert("mami","mami");
		Scanner sc = new Scanner(System.in);
		String s;
		s = sc.next();
		int marca = 0;
		while (s.compareTo("end") != 0) {
			//if (rt.contains(s)) System.out.println("Si");
			//else System.out.println("No");
			//System.out.println(rt.complete(s));
			//rt.insert(s, s);
			System.out.println(rt.count_within_distance(s,2,marca++));
			//ArrayList<String> al = rt.searchPrefix(s, 2);
			//print(al);
			s = sc.next();
		}
		//rt.printTree();
		System.out.println(rt.getSize());
		sc.close();*/
		final long endTime = System.currentTimeMillis();
		System.out.println("Total Building time: " + (endBuild - startTime) + " milliseconds" );
		System.out.println("Total processing time: " + (endTime - endBuild) + " milliseconds" );

	}
	
	private static void readInput(RadixTreeImpl<String> rt, String fileName) throws IOException {
	    Path path = Paths.get(fileName);
	    try (BufferedReader reader = Files.newBufferedReader(path,StandardCharsets.UTF_8)){
	      String line = null;
	      while ((line = reader.readLine()) != null) {
	    	  rt.insert(line, line);
	      }      
	    }		  
	}
	
	/*private static void processQueries(RadixTreeImpl<String> rt, String fileName, int distance) throws IOException {
		Path path = Paths.get(fileName);
	    try (BufferedReader reader = Files.newBufferedReader(path,StandardCharsets.UTF_8)){
	      String line = null;
	      int marca = 0;
	      while ((line = reader.readLine()) != null) {
	    	String[] parts = line.split(" ");
	        System.out.println(rt.count_within_distance(parts[0], distance, marca++));
	        System.out.println(rt.count_within_distance(parts[1], distance, marca++));
	      }      
	    }
	}*/
	
	private static void processQueries(RadixTreeImpl<String> rt, String fileName, int distance) throws IOException {
		Path path = Paths.get(fileName);
	    try (BufferedReader reader = Files.newBufferedReader(path,StandardCharsets.UTF_8)){
	      String line = null;
	      int marca = 0;
	      while ((line = reader.readLine()) != null) 
	        System.out.println(rt.count_within_distance(line, distance, marca++));	            
	    }
	}
	
	private static void print(ArrayList<String> al) {
		ListIterator<String> it = al.listIterator();
		while (it.hasNext()) {
			String s = it.next();
			System.out.println(s);
		}
	}

}
