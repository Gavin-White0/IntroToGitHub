#include <iostream>
using namespace std;

bool isValidBase(char base){
    if(base == 'A' || base == 'C' || base == 'G' || base == 'T'){
        return true;
    }
    else{
        return false;
    }
}

bool isValidStrand(string strand){
    int correct_bases = 0;
    for(int i =0; i < (int)strand.length(); i++){
        switch(strand.at(i)){
            case 'A':
            case 'C':
            case 'T':
            case 'G': correct_bases++ ;
            break;
        }
    }
    if((int)strand.length() == 0){
        return false;
    }
    if(correct_bases == (int)strand.length()){
        return true;
    }
    else{
        return false;
    }
}

double strandSimilarity(string strand1, string strand2){
    if(strand1.length() != strand2.length()){
        return 0;
    }
    double similarities = 0;
    double strand_length = (int)strand1.length();
    for(int i =0; i < strand_length; i++){
        if(strand1.at(i) == strand2.at(i)){
            similarities++;
        }
    }

    return (similarities / strand_length);
}

int bestStrandMatch(string input_strand,string target_strand){

    int difference_in_length = input_strand.length() - target_strand.length();
    if(difference_in_length < 0){
        difference_in_length *= -1;
    }
    double best_similarity_score = 0.0;
    int index = 0;
    double similarity_score = 0.0;

    for(int i=0; i <= difference_in_length; i++){
        string input_sub_strand = input_strand.substr(i, target_strand.length());

        similarity_score = strandSimilarity(input_sub_strand, target_strand);
        
        if(similarity_score > best_similarity_score){
            best_similarity_score = similarity_score;
            index = i;
        }
    }
    if(best_similarity_score > 0){
        cout<<"Best similarity score: "<<best_similarity_score<<endl;
    }
    else if(best_similarity_score == 0){
        cout<<"Best similarity score: 0.0"<<endl;
    }
    return index;
} 

void identifyMutations(string input_strand, string target_strand){
    
    int target_length = target_strand.length();
    int input_length = input_strand.length();

    // if both are exactly the same
    if(input_strand == target_strand){
        int index = bestStrandMatch(target_strand, input_strand);
        cout << "Best alignment index: " << index << endl;
        cout << "No mutations found." << endl;
    }

    // target strand longer than input
    else if(target_length > input_length){
        int index = bestStrandMatch(target_strand, input_strand);
        cout << "Best alignment index: " << index << endl;

        // Insertions before matching part
        for(int i = 0; i < index; i++){
            cout << "Insertion at position " << (i + 1) << ": " << target_strand.at(i)
                 << " is inserted in target strand" << endl;
        }

        // Substitutions where strands overlap
        for (int i = 0, counter = index; i < input_length && counter < target_length; i++, counter++){
            if (target_strand.at(counter) != input_strand.at(i)){
                cout << "Substitution at position " << counter + 1 << ": " << input_strand.at(i)
                     << " -> " << target_strand.at(counter) << endl;
            }
        }

        // Insertions after matching part
        for(int i = index + input_length; i < target_length; i++){
            cout << "Insertion at position " << i + 1 << ": " << target_strand.at(i)
                 << " is inserted in target strand" << endl;
        }
    }

    // input strand longer than target
    else if(input_length > target_length){
        int index = bestStrandMatch(input_strand, target_strand);
        cout << "Best alignment index: " << index << endl;

        // Deletions before matching part
        for(int i = 0; i < index; i++){
            cout << "Deletion at position " << (i + 1) << ": " << input_strand.at(i)
                 << " is deleted in target strand" << endl;
        }

        // Substitutions where strands overlap
        for (int i = 0, counter = index; i < target_length && counter < input_length; i++, counter++){
            if (input_strand.at(counter) != target_strand.at(i)){
                cout << "Substitution at position " << counter + 1 << ": " << input_strand.at(counter)
                     << " -> " << target_strand.at(i) << endl;
            }
        }

        // Deletions after matching part
        for(int i = index + target_length; i < input_length; i++){
            cout << "Deletion at position " << (i + 1) << ": " << input_strand.at(i)
                 << " is deleted in target strand" << endl;
        }
    }

    // If strands are the same length but not the same structure (substitutions only)
    else{
        int index = bestStrandMatch(target_strand, input_strand);
        cout << "Best alignment index: " << index << endl;

        // Substitutions for same length strands
        for(int i = 0; i < target_length; i++){
            if(target_strand.at(i) != input_strand.at(i)){
                cout << "Substitution at position " << (i + 1) << ": " << input_strand.at(i)
                     << " -> " << target_strand.at(i) << endl;
            }
        }
    }
}

void transcribeDNAtoRNA(string strand){
    int strand_length = strand.length();
    for(int i=0;i < strand_length; i++){
        if(strand.at(i) == 'T'){
            strand.at(i) = 'U';
        }
    }
    cout<<strand<<endl;
}

void reverseComplement(string strand){
    int strand_length = strand.length();
    string strand_compliment;
    strand_compliment.resize(strand_length);
    for(int i=0; i < strand_length; i++){
        if(strand.at(i) == 'A'){
            strand_compliment.at(i) = 'T';
        }
        if(strand.at(i) == 'T'){
            strand_compliment.at(i) = 'A';
        }
        if(strand.at(i) == 'C'){
            strand_compliment.at(i) = 'G';
        }
        if(strand.at(i) == 'G'){
            strand_compliment.at(i) = 'C';
        }
    }
    for(int i = 0; i < strand_length/2; i++){
        char temp = strand_compliment.at(i);
        strand_compliment.at(i) = strand_compliment.at(strand_length - i - 1);
        strand_compliment.at(strand_length - 1 - i) = temp;
    }
    cout<<strand_compliment<<endl;
}

void getCodingFrames(string strand) {
    // Create variables for start and end index, new strand, and boolean for frame found
    int end_index = -1;
    int start_index = -1;
    string new_strand = "";
    bool frame_found = false;
    int strand_length = strand.length();
    
    // Loop through the strand to find
    for (int i = 0; i < strand_length - 2; i++) {
        // Check if the current codon is the proper start codon
        if (strand.at(i) == 'A' && strand.at(i+1) == 'T' && strand.at(i+2) == 'G') {
            start_index = i;
            
            // Loop to find stop codons
            for (int j = start_index; j < strand_length - 2; j += 3) {
                if ((strand.at(j) == 'T' && strand.at(j+1) == 'A' && strand.at(j+2) == 'A') ||
                    (strand.at(j) == 'T' && strand.at(j+1) == 'A' && strand.at(j+2) == 'G') ||
                    (strand.at(j) == 'T' && strand.at(j+1) == 'G' && strand.at(j+2) == 'A')) {

                    end_index = j;

                    // Validate that the length is a multiple of 3
                    if ((end_index - start_index) % 3 == 0) {
                        for (int k = start_index; k < (end_index + 3); k++) {
                            new_strand += strand.at(k);
                        }
                        cout << new_strand << endl; // Output the reading frame
                        frame_found = true;
                        new_strand = ""; // Reset the new strand
                        start_index = -1; // Reset start index
                        i = end_index + 2; // Move to next codon after stop codon
                    }
                    break;
                }
            }
        }
    }
    if (!frame_found) {
        cout << "No reading frames found." << endl;
    }
}

void printMenu(){
    cout<<"--- DNA Analysis Menu ---"<<endl;
    cout<<"1. Calculate the similarity between two sequences of the same length"<<endl;
    cout<<"2. Calculate the best similarity between two sequences of either equal or unequal length"<<endl;
    cout<<"3. Identify mutations"<<endl;
    cout<<"4. Transcribe DNA to RNA"<<endl;
    cout<<"5. Find the reverse complement of a DNA sequence"<<endl;
    cout<<"6. Extract coding frames"<<endl;
    cout<<"7. Exit"<<endl;
    cout<<"Please enter your choice (1 - 7):"<<endl;
}

int main(){
    int input = 0;
    while(input != 7){
        if(input < 1 || input > 7){
            while(input < 1 || input > 7){
                printMenu();
                cin>>input;
                if(input < 1 || input > 7){
                    cout<<"Invalid input. Please select a valid option."<<endl;
                }
            }
        }
        string strand_1 = "";
        string strand_2 = "";
        double similarity_score = 0.0;

        switch (input)
        {
        case 1: 
            while(!isValidStrand(strand_1)){
                cout<<"Enter the first DNA sequence:"<<endl;
                cin>>strand_1;
                if(!isValidStrand(strand_1)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                }
            }
            while(!isValidStrand(strand_2)){
                cout<<"Enter the second DNA sequence:"<<endl;
                cin>>strand_2;
                if(!isValidStrand(strand_2)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                }
            }

            if(strand_1.length() != strand_2.length()){
                cout<<"Error: Input strands must be of the same length."<<endl;
                input = 0;
                break;
            }
            else{
                similarity_score = strandSimilarity(strand_1, strand_2);
                cout<<"Similarity score: "<<similarity_score<<endl;
            }
        input = 0;
        break;

        case 2:
            while(!isValidStrand(strand_1)){
                cout<<"Enter the first DNA sequence:"<<endl;
                cin>>strand_1;
                if(!isValidStrand(strand_1)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                }
            }
            while(!isValidStrand(strand_2)){
                cout<<"Enter the second DNA sequence:"<<endl;
                cin>>strand_2;
                if(!isValidStrand(strand_2)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                }
            }
            similarity_score = bestStrandMatch(strand_1, strand_2);
        input = 0;
        break;

        case 3:
            while(!isValidStrand(strand_1)){
                cout<<"Enter the first DNA sequence:"<<endl;
                cin>>strand_1;
                if(!isValidStrand(strand_1)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                }
            }
            while(!isValidStrand(strand_2)){
                cout<<"Enter the second DNA sequence:"<<endl;
                cin>>strand_2;
                if(!isValidStrand(strand_2)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                }
            }
            identifyMutations(strand_1, strand_2);

        input = 0;
        break;

        case 4:
            while(!isValidStrand(strand_1)){
                cout<<"Enter the DNA sequence to be transcribed:"<<endl;
                cin>>strand_1;
                if(!isValidStrand(strand_1)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                }
            }
            cout<<"The transcribed DNA is: ";
            transcribeDNAtoRNA(strand_1);

        input = 0;
        break;

        case 5:
            while(!isValidStrand(strand_1)){
                cout<<"Enter the DNA sequence:"<<endl;
                cin>>strand_1;
                if(!isValidStrand(strand_1)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                }
            }
            cout<<"The reverse complement is: ";
            reverseComplement(strand_1);

        input = 0;
        break;
            
        case 6:
            while(!isValidStrand(strand_1)){
                cout<<"Enter the DNA sequence:"<<endl;
                cin>>strand_1;
                if(!isValidStrand(strand_1)){
                    cout<<"Invalid input. Please enter a valid sequence."<<endl;
                }
            }
            cout<<"The extracted reading frames are:"<<endl;
            getCodingFrames(strand_1);
        input = 0;    
        break;
        }
    }

    cout<<"Exiting program."<<endl;
    return 0;
}