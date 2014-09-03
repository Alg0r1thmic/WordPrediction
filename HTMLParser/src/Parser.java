import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.nodes.Node;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;


public class Parser {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String html="";
		try {
			html = new Scanner(new File("/home/mmayo/code/learning_words/tools/html.out")).useDelimiter("\\Z").next();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Document doc = Jsoup.parse(html);
		Element link = doc.select("div#resultStats").first();

		/*String text = doc.body().text(); // "An example link"
		System.out.println(text);
		String linkHref = link.attr("href"); // "http://example.com/"
		System.out.println(linkHref);
		String linkText = link.text(); // "example""
		System.out.println(linkText);

		String linkOuterH = link.outerHtml(); 
		    // "<a href="http://example.com"><b>example</b></a>"
		System.out.println(linkOuterH);
		String linkInnerH = link.html(); // "<b>example</b>"
		System.out.println(linkInnerH);*/
		System.out.println(link.text());
	}

}
