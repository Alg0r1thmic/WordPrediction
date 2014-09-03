import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.io.Writer;
import java.util.Scanner;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;


public class RetrieverParser {
	
	public static String myparser(String s) {
		String parts[] = s.split(" ");
		String new_string = "";
		for (int i=0; i<parts[1].length(); i++) {
			if (parts[1].charAt(i)==',') continue;
			else new_string += parts[1].charAt(i);
		}
			
		return new_string;
	}

	public static void main(String[] args) throws IOException {
		
		BufferedWriter bw = null;
		
		try {			  
			File file = new File("/home/mmayo/code/learning_words/sets/all_words_unique_webhits.txt");
 
			// if file doesnt exists, then create it
			if (!file.exists()) {
				file.createNewFile();
			}
 
			FileWriter fw = new FileWriter(file.getAbsoluteFile());
			bw = new BufferedWriter(fw);
 
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		BufferedReader br = new BufferedReader(new FileReader("/home/mmayo/code/learning_words/sets/all_words_unique.txt"));
		String line;
		while ((line = br.readLine()) != null) {
			//String url = "https://search.yahoo.com/search?p="+line;
			String url = "https://www.google.com/search?q="+line;
			Document doc = null;
			try {
				doc = Jsoup.connect(url).userAgent("Mozilla/5.0").get();
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			//Element link = doc.select("div#pg").select("span").first();
			Element link = doc.select("div#resultStats").first();
			String txt = myparser(link.text());
			try {
				bw.write(txt+"\n");
				bw.flush();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			int randomNum = 0 + (int)(Math.random()*100); 
			try {
			    Thread.sleep(30035+randomNum);
			} catch(InterruptedException ex) {
			    Thread.currentThread().interrupt();
			}
		}
		bw.close();
		br.close();
		
		
	}

}
