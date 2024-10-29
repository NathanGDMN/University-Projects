package Lab5;

public class Triple <T, U> {

	T A;
	U B;
	T C;
	
	/*Constructors*/
	public Triple() {
		A = null;
		B = null;
		C = null;
	}
	
	public Triple(T firstItem, U secondItem, T thirdItem) {
		A = firstItem;
		B = secondItem;
		C = thirdItem;
	}
	
	/*Methods*/
	public boolean equals(Triple<T, U> otherTriple) {
		if (this.A.equals(otherTriple.A) && this.B.equals(otherTriple.B) && this.C.equals(otherTriple.C)) {
			return true;
		}else {
			return false;
		}
	}
	
	public String toString(){
		String str = A.toString() + " " + B.toString() + " " + C.toString();
		return str;
	}
}
