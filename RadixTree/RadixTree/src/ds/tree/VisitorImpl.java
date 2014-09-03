package ds.tree;

import java.io.Serializable;


/**
 * A simple standard implementation for a {@link visitor}.
 * 
 * @author Dennis Heidsiek 
 * @param <T,R>
 */
public abstract class VisitorImpl<T, R> implements Visitor<T, R>, Serializable  {

    /**
	 * 
	 */
	private static final long serialVersionUID = -4247949587816084920L;
	protected R result;
    
    
	public VisitorImpl() {
		this.result = null;
	}
	
	public VisitorImpl(R initialValue) {
		this.result = initialValue;
	}
	
	public R getResult() {
		return result;
	}
	
	abstract public void visit(String key, RadixTreeNode<T> parent, RadixTreeNode<T> node);
}