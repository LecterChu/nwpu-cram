    #include "DNASequence.h"

	DNASequence::DNASequence(string initialSequence, int initialNumberOfA)  {

		sequence = initialSequence;
		numberOfA = initialNumberOfA;
		countNucleotides();
	}
	void DNASequence::countNucleotides() {
		int index = 0;
		while (index < sequence.length()) {
			char nucleotide = sequence[index];
			if (nucleotide == 'A') {
				numberOfA++;
			}
			index++;
		}
		return;
	}

	int  DNASequence::getNumberOfA( )  {

		return numberOfA;
	}


    bool  DNASequence::twoConsecutive(char input)  {

		int index = 1;
		while (index < sequence.length() - 1) {
			int indexOfFirstNucleotide = index - 1;
			char firstNucleotide = sequence[indexOfFirstNucleotide];
			char secondNucleotide = sequence[index];
			if ((firstNucleotide == input) || (secondNucleotide == input)) {
				return true;
			}
			index++;
		}

		return false;
	}

