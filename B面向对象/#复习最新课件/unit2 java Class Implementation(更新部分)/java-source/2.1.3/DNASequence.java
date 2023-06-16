/**
 * This class represents a DNA sequence of nucleotides 'A', 'T', 'C' and 'G'
 * as a sequence of characters in a {@link String} object.
 *
 * @author  author name
 * @version  1.0.0
 */
public class DNASequence  {

	/* Contains the sequence of nucleotides. */
	private String  sequence;

	/* Contains the number of nucleotide A */
	private int numberOfA;

	/* Contains the number of nucleotide T */
	private int numberOfT;

	/* Contains the number of nucleotide C */
	private int numberOfC;

	/* Contains the number of nucleotide G */
	private int numberOfG;

	/**
	 * Test driver for class <code>DNA</code>.
	 *
	 * @param args  not used.
	 */
	public static void  main(String[] args)  {

		String s = "ATTATCGGGGTAA";
		DNASequence dnaSequence = new DNASequence(s);

		if ((dnaSequence.getNumberOfA() == 4)
				&& (dnaSequence.getNumberOfT() == 4)
				&& (dnaSequence.getNumberOfC() == 1)
				&& (dnaSequence.getNumberOfG() == 4)) {
			System.out.println("Test case 1:  get methods passed\n");
		} else {
			System.out.println("Test case 1:  get methods failed !!!\n");
		}

		if (dnaSequence.twoConsecutive('T')) {
			System.out.println("Test case 2: method twoConsecutive passed\n");
		} else {
			System.out.println(
				"Test case 2: method twoConsecutive failed !!!\n");
		}

		if (dnaSequence.twoConsecutive('A')) {
			System.out.println("Test case 3: method twoConsecutive passed\n");
		} else {
			System.out.println(
				"Test case 3: method twoConsecutive failed !!!\n");
		}

		if (!dnaSequence.twoConsecutive('C')) {
			System.out.println("Test case 4: method twoConsecutive passed\n");
		} else {
			System.out.println(
				"Test case 4: method twoConsecutive failed !!!\n");
		}
	}

	/**
	 * Constructs a <code>DNASequence</code> object that represents the sequence
	 * of nucleotides indicated by the chars in the <code>string</code> argument
	 * and counts the occurrences of each nucleotide in the sequence.
	 *
	 * @param initialSequence  a string with the initial sequence of nucleotides.
	 */
	public  DNASequence(String initialSequence)  {

		sequence = initialSequence;
		countNucleotides();
	}

	/*
	 * Counts the occurrences of each nucleotide in the DNA sequence and then
	 * updates the values of the variables numberOfA, numberOfT, numberOfC, and
	 * numberOfG .
	 */
	private void  countNucleotides()  {

		int index = 0;

		while (index < sequence.length()) {

			char nucleotide = sequence.charAt(index);

			if (nucleotide == 'A') {
				numberOfA++;
			} else if (nucleotide == 'T') {
				numberOfT++;
			} else if (nucleotide == 'C') {
				numberOfC++;
			} else if (nucleotide == 'G') {
				numberOfG++;
			}
			index++;
		}

		return;
	}

	/**
	 * Obtains the number of occurrences of nucleotide A in the sequence.
	 *
	 * @return  the number of occurrences of nucleotide A.
	 */
	public int  getNumberOfA( )  {

		return numberOfA;
	}

	/**
	 * Obtains the number of occurrences of nucleotide T in the sequence.
	 *
	 * @return  the number of occurrences of nucleotide T.
	 */
	public int  getNumberOfT( )  {

		return numberOfT;
	}

	/**
	 * Obtains the number of occurrences of nucleotide C in the sequence.
	 *
	 * @return  the number of occurrences of nucleotide C.
	 */
	public int  getNumberOfC( )  {

		return numberOfC;
	}

	/**
	 * Obtains the number of occurrences of nucleotide G in the sequence.
	 *
	 * @return  the number of occurrences of nucleotide G.
	 */
	public int  getNumberOfG( )  {

		return numberOfG;
	}

	/**
	 * Checks if the nucleotide specified by the argument occurs in two
	 * consecutive locations in the DNA sequence.
	 *
	 * @param input a <code>char</code> that represent the nucleotide.
	 * @return  <code>true</code> if the specified nucleotide occurs two
	 *          consecutive locations in the sequence. 
	 *          Returns <code>false</code> otherwise.
	 */
	public boolean  twoConsecutive(char input)  {

		int index = 1;

		while (index < sequence.length() - 1) {

			int indexOfFirstNucleotide = index - 1;

			char firstNucleotide = sequence.charAt(indexOfFirstNucleotide);
			char secondNucleotide = sequence.charAt(index);

			if ((firstNucleotide == input) || (secondNucleotide == input)) {

				return true;

			}
			index++;
		}

		return false;
	}
}
