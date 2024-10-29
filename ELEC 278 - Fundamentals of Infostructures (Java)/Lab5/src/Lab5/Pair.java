package Lab5;

public class Pair <T> {
	
	private T A; 
	private T B; 
	
	
	/*Constructors*/
	public Pair() {
		A = null;
		B = null;
	}
	
	public Pair(T firstItem, T secondItem) {
		A = firstItem;
		B = secondItem;
	}
	
	/*Methods*/
	public boolean equals(Pair<T> otherPair) {
		if (this.A.equals(otherPair.A) && this.B.equals(otherPair.B)) {
			return true;
		}else {
			return false;
		}
	}
	
	public String toString(){
		String str = A.toString() + " " + B.toString();
		return str;
	}
}
