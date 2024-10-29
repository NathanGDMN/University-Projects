package Lab5;

import java.util.ArrayList;
import java.util.Random;
import java.util.Date;

public class Lab5 {
	
	public static void main(String[] args)
    {
		ArrayList<Integer> intArray = new ArrayList<Integer>(5); 
		
		for (int i = 0; i < 10; i++) { //Adds ten random numbers between 0 and 99 to intArray
			intArray.add((int)(Math.random()*100));
		}
		
		ArrayList<Integer> revIntArray = new ArrayList<Integer>();
		
		for(int x : intArray) { //For each integer in intArray, add it to revIntArray at index 0
			revIntArray.add(0, x);
		}
		
		System.out.println(intArray.toString());
		System.out.println(revIntArray.toString());
		
		ArrayList<HourlyEmployee> hEmployeeArray = new ArrayList<HourlyEmployee>(100);
		
		for (int i = 0; i < 4; i++) {
			hEmployeeArray.add(new HourlyEmployee());
		}
		
		System.out.println(hEmployeeArray.toString());
		System.out.println("size: " +hEmployeeArray.size());
		
		Date date = new Date();
		HourlyEmployee Marcus = new HourlyEmployee("Marcus", date, 20.0, 0.0);
		
		hEmployeeArray.set(0, Marcus);
		
		System.out.println(hEmployeeArray.toString());
		
		hEmployeeArray.remove(3);
		hEmployeeArray.trimToSize();
		
		Pair<String> couple1 = new Pair<String>("Jeremy", "Jenny");
		Pair<String> couple2 = new Pair<String>("Jeremy", "Jenny");
		Pair<String> couple3 = new Pair<String>("Joseph", "Jill");
		
		System.out.println("couple1: " + couple1.toString());
		System.out.println("couple2: " + couple2.toString());
		System.out.println("couple3: " + couple3.toString());
		
		System.out.println("Couple1 and Couple2 should be equal. " + couple1.equals(couple2));
		System.out.println("Couple1 and Couple3 should not be equal. " + !(couple1.equals(couple3)));
		
		Triple<String, Double> Trip1 = new Triple<>("Toronto", 264.5, "Montreal");
		Triple<String, Double> Trip2 = new Triple<>("Toronto", 264.5, "Montreal");
		Triple<String, Double> Trip3 = new Triple<>("Toronto", 264.5, "Kingston");
		
		System.out.println("Trip1: " + Trip1.toString());
		System.out.println("Trip2: " + Trip2.toString());
		System.out.println("Trip3: " + Trip3.toString());
		
		System.out.println("Trip1 and Trip2 should be equal. " + Trip1.equals(Trip2));
		System.out.println("Trip1 and Trip3 should not be equal. " + !(Trip1.equals(Trip3)));
    }
	
}
