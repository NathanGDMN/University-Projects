package a2;

import java.awt.Color;
import java.util.ArrayList;
import java.util.TreeSet;

/**
 * Methods useful for implementing the game Wordle. None of the methods
 * assume that the guess or answer words have exactly 5 letters.
 */
public class WordleUtils {

	/**
	 * Returns a new string formed by replacing one character in the string
	 * {@code s} with the replacement character {@code c}. The position of the
	 * replaced character is given by {@code index}.
	 * 
	 * @param s     a string to replace one character in
	 * @param index the index of the replaced character
	 * @param c     the character to use as the replacement character
	 * @return a new string formed by replacing one character in s with the
	 *         replacement character c
	 * @throws IndexOutOfBoundsException if index is not a valid index for the
	 *                                   string s
	 */
	public static String replace(String s, int index, char c) {
		if (index < 0 || index >= s.length()) { //If index does not match word
			throw new IndexOutOfBoundsException();
		}
		
		return s.substring(0, index) + c + s.substring(index + 1);
	}

	/**
	 * Returns a list indicating which letters in the {@code guess} string match
	 * letters in the {@code answer} string. Letters match if they are equal and
	 * have the same location in both strings.
	 * 
	 * <p>
	 * The returned list contains the value {@code true} at index {@code i} if the
	 * characters at index {@code i} of the {@code guess} and {@code answer} strings
	 * are equal, otherwise the the value at index {@code i} is {@code false}.
	 * 
	 * @param guess  a string to compare to the answer
	 * @param answer the answer string
	 * @return a list of boolean values indicating whether characters in the guess
	 *         and answer strings match
	 * @throws IllegalArgumentException if guess and answer have different lengths
	 */
	public static ArrayList<Boolean> isGreen(String guess, String answer) {
		if (guess.length() != answer.length()) {
			throw new IllegalArgumentException("s.length() != target.length()");
		}
		
		char[] gues = guess.toCharArray();
		char[] answ = answer.toCharArray();
		ArrayList<Boolean> boolList =  new ArrayList<>(); //Boolean list that will be returned
		
		for (int i = 0; i < guess.length(); i++) {
			if (gues[i] == answ[i]) {
				boolList.add(true);
			} else {
				boolList.add(false);
			}
		}
		
		return boolList;
	}

	/**
	 * Returns a list indicating which letters in the {@code guess} string also
	 * appear in the {@code answer} string taking into account how many times a
	 * letter appears; see the assignment document for some examples.
	 * 
	 * <p>
	 * The returned list contains the value {@code true} at index {@code i} if the
	 * character at index {@code i} of the {@code guess} appears in the
	 * {@code answer} string (again, accounting for the number of times the letter
	 * appears), otherwise the the value at index {@code i} is {@code false}.
	 * 
	 * @param guess  a string to compare to the answer
	 * @param answer the answer string
	 * @return a list of boolean values indicating whether characters in the guess
	 *         string appear in the answer string accounting for the number of times
	 *         that the character appears
	 * @throws IllegalArgumentException if guess and answer have different lengths
	 */
	public static ArrayList<Boolean> isYellow(String guess, String answer) {
		if (guess.length() != answer.length()) {
			throw new IllegalArgumentException("s.length() != target.length()");
		}
		
		ArrayList<Boolean> green = new ArrayList<>();
		green = isGreen(guess, answer);
		
		ArrayList<Boolean> yellow = new ArrayList<>();//Array to be returned
		
		for (int i = 0; i < guess.length(); i++) { //Remove all characters where isGreen is true
			boolean g = green.get(i);
			if (g == true) {
				guess = replace(guess, i, '1');
				answer = replace(answer, i, '2');
			}
		}
		
		//Yellow Algorithm
		for (int i = 0; i < guess.length(); i++) { //Compares each letter in guess to each letter in answer
			
			yellow.add(false); 
			
			for (int j = 0; j < guess.length(); j++) {
				if (guess.charAt(i) == answer.charAt(j)) { //If letter in guess matches letter in answer, replace both letters in guess and answer so they wont match again, remove false and add true to Arraylist.
					guess = replace(guess, i, '1');
					answer = replace(answer, j, '2');
					yellow.remove(i);
					yellow.add(true);
					break;
				}
			}
		}
		
		return yellow;
	}
	
	

	/**
	 * Returns a list of the colorings for the given guess and answer words. See the
	 * assignment document for details on how letters of the guess word are colored
	 * in the game Wordle.
	 * 
	 * @param guess  a guess word
	 * @param answer the answer word
	 * @return a list of the colorings for the given guess and answer words
	 * @throws IllegalArgumentException if guess and answer have different lengths
	 */
	public static ArrayList<WordleColor> getColors(String guess, String answer) {
		if (guess.length() != answer.length()) {
			throw new IllegalArgumentException();
		}
		
		ArrayList<Boolean> green = new ArrayList<>();
		green = isGreen(guess, answer);
		
		ArrayList<Boolean> yellow = new ArrayList<>();
		yellow = isYellow(guess, answer);
		
		ArrayList<WordleColor> colors = new ArrayList<>();
		
		
		for (int i = 0; i < guess.length(); i++) {
			boolean g = green.get(i);
			boolean y = yellow.get(i);
			
			if (g == true) {
				colors.add(WordleColor.GREEN);
				continue;
			}
			if (y == true) {
				colors.add(WordleColor.YELLOW);
				continue;
			}
			colors.add(WordleColor.GRAY);
		}
		
		return colors;
	}

	/**
	 * Update the sets of different letter categories in a game of Wordle given the
	 * guess and answer words. This method is meant to be called after the player
	 * makes a new guess. The first time that the method is called for a new game of
	 * Wordle, the sets {@code included} and {@code excluded} should be empty, and
	 * the set {@code possible} should contain the letters {@code 'A'} through
	 * {@code 'Z'}.
	 * 
	 * <p>
	 * The set {@code included} is the set of letters that the player has determined
	 * must be in the answer word.
	 * 
	 * <p>
	 * The set {@code excluded} is the set of letters that the player has determined
	 * must not be in the answer word.
	 * 
	 * <p>
	 * The set {@possible} is the set of letters that have not been used yet by the
	 * player. If {@code guess.equals(answer)} is {@code true} then the set
	 * {@possible} will be empty.
	 * 
	 * @param guess    the most recent guess word
	 * @param answer   the answer word
	 * @param included the set of letters that the player has determined are in the
	 *                 answer word
	 * @param excluded the set of letters that the player has determined are not in
	 *                 the answer word
	 * @param possible the set of letters not in included or excluded
	 * @throws IllegalArgumentException if guess and answer have different lengths
	 */
	public static void updateLetters(String guess, String answer, 
			TreeSet<Character> included,
			TreeSet<Character> excluded, 
			TreeSet<Character> possible) {
		
		ArrayList<WordleColor> colors = new ArrayList<>();
		colors = getColors(guess, answer);
		
		String ans = answer.toUpperCase(); //So that included and excluded sets only contain capitalized letters
		String gue = guess.toUpperCase();
		char[] a = ans.toCharArray();
		char[] g = gue.toCharArray();
		
		for(int i = 0; i < guess.length(); i++) {
			char c = g[i];
			possible.remove(c); //Remove letter from possible set
			
			if (colors.get(i) == WordleColor.GRAY) {
				// add to excluded only if not already in included
				if (!included.contains(c)) {
					excluded.add(c);
				}
			}else {
				included.add(c);
				excluded.remove(c); //A letter might be in excluded if guess contains duplicate letters
			}
		}
		
	}

	public static void main(String[] args) {
		// simulates one game of Wordle
		
		// set up the sets of letters
		TreeSet<Character> in = new TreeSet<>();
		TreeSet<Character> notIn = new TreeSet<>();
		TreeSet<Character> mightBeIn = new TreeSet<>();
		for (char c = 'A'; c <= 'Z'; c++) {
			mightBeIn.add(c);
		}
		
		// the answer
		String ans = "CORAL";

		// the guesses
		final String[] GUESSES = { "VEGAN", "HULAS", "BLOAT", "LOYAL",  "FOCAL", "CORAL"};
		int guessNum = 0;
		for (String g : GUESSES) {
			guessNum++;
			System.out.println("answer  : " + ans);
			System.out.println("guess " + guessNum + " : " + g);
			System.out.println("isGreen : " + WordleUtils.isGreen(g, ans));
			System.out.println("isYellow: " + WordleUtils.isYellow(g, ans));
			System.out.println("colors  : " + WordleUtils.getColors(g, ans));
			WordleUtils.updateLetters(g, ans, in, notIn, mightBeIn);
			System.out.println("in      : " + in);
			System.out.println("not in  : " + notIn);
			System.out.println("maybe?  : " + mightBeIn);
			System.out.println();
		}

	}

}
