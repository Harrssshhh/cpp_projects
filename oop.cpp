#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

class Candidate {
public:
    string name;
    int votes;

    Candidate() : votes(0) {}
    Candidate(const string& candidateName) : name(candidateName), votes(0) {}
};

class VotingSystem {
private:
    int NumCan;
    int NumStu;
    vector<Candidate> candidates;
    unordered_set<string> votedIDs;

public:
    VotingSystem() {}

    void setNumCandidates(int num) {
        NumCan = num;
        candidates.resize(NumCan + 1); 
    }

    void setNumStudents(int num) {
        NumStu = num;
    }

    void inputCandidates() {
        for (int i = 1; i <= NumCan; i++) {
            cout << "Candidate-" << i << " Name: ";
            cin.ignore();
            getline(cin, candidates[i].name);
        }
    }

    void Voting() {
        for (int i = 1; i <= NumStu; i++) {
            cout << endl << "                     Voting System                " << endl;
            cout << endl << "                  Student - " << i << endl;
            cout << "............................................................." << endl;
            cout << endl;

            string inputid;

            cout << "Enter Your Roll no: ";
            cin >> inputid;

            if (votedIDs.find(inputid) != votedIDs.end()) {
                cout << "Sorry! You have already voted. Please try again with a different student." << endl;
                i--;  
                continue;
            }

            cout << " " << endl;
            displayCandidates();

            int vote;
            cout << "Now, Vote for above candidate (1-" << NumCan << "): ";
            cin >> vote;

            if (vote < 1 || vote > NumCan) {
                cout << "Invalid vote. Please vote for a valid candidate." << endl;
                i--;
                continue;
            }

            record(inputid, vote);
            votedIDs.insert(inputid);
        }

        Result();
    }

private:
    void displayCandidates() {
        for (int j = 1; j <= NumCan; j++) {
            cout << "Press " << j << " for " << candidates[j].name << endl;
        }
        cout << " " << endl;
    }

    void record(const string& inputid, int vote) {
        ofstream fileVoteDone("VoteDoneBy.txt", ios::app);
        if (fileVoteDone.is_open()) {
            fileVoteDone << inputid << "\n";
            fileVoteDone.close();
        }

        ofstream fileVoteDetails("VoteDetails.txt", ios::app);
        if (fileVoteDetails.is_open()) {
            fileVoteDetails << inputid << " voted for " << candidates[vote].name << "\n";
            fileVoteDetails.close();
        }

        candidates[vote].votes++;
        cout << endl << "Thanks for your vote. ";
        cin.ignore();
        cin.get();
    }

    void Result() {
        if (votedIDs.size() == NumStu) {
            bool sameVotes = samevote();

            if (sameVotes) {
                cout << endl << "All candidates have the same number of votes. Revoting is required!" << endl;
                Revote();
            } else {
    
                displayResult();
            }
        } else {
            cout << "Voting is still in progress. Results will be displayed after all students have voted." << endl;
        }
    }

    bool samevote() {
        int votes = candidates[1].votes;

        for (int j = 2; j <= NumCan; j++) {
            if (candidates[j].votes != votes) {
                return false;
            }
        }

        return true;
    }

    void Revote() {
        cout << "Resetting votes for a revote..." << endl;


        for (int j = 1; j <= NumCan; j++) {
            candidates[j].votes = 0;
        }
        votedIDs.clear();
        Voting();
    }

    void displayResult() {
        
        for (int j = 1; j <= NumCan; j++) {
            if (candidates[j].votes > 0) {
                cout << candidates[j].name << " received " << candidates[j].votes << " votes, which is "
                     << (static_cast<double>(candidates[j].votes) / votedIDs.size()) * 100 << "% of the total votes." << endl;
            }
        }

        int maxVotes = 0;
        for (int j = 1; j <= NumCan; j++) {
            if (maxVotes < candidates[j].votes) {
                maxVotes = candidates[j].votes;
            }
        }
        for (int j = 1; j <= NumCan; j++) {
            if (maxVotes == candidates[j].votes) {
                cout << endl << "Congratulations " << candidates[j].name << "! You have the highest votes." << endl;
                break;
            }
        }
    }
};

int main() {
    VotingSystem votingSystem;

    cout << endl << " ..........................Voting System..............................." << endl;
    cout << endl;
    cout << endl;

    int NumCan;
    cout << endl << "    Number of Candidates: ";
    cin >> NumCan;

    if (NumCan > 1) {
        votingSystem.setNumCandidates(NumCan);
        votingSystem.inputCandidates();

        int NumStu;
        cout << "    Number of Students: ";
        cin >> NumStu;

        cout << endl << "  Thank You, Admin! We are going to start our election with " << NumStu << " Students and " << NumCan << " Candidates." << endl;
        cout << "......................................................................" << endl;
        cout << endl;

        votingSystem.setNumStudents(NumStu);
        votingSystem.Voting();
    }

    cin.ignore();
    cin.get();

    return 0;
}
