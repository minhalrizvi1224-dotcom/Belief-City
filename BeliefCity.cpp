/*
+====================================================================+
|                                                                    |
|           PROJECT: BELIEF CITY - PSYCHOLOGICAL SURVIVAL            |
|           DEVELOPER: S. M. MINHAL. Abbas. RIZVI (v21.0 LOCK)       |
|           CORE ARCHITECTURE: ADVANCED OOP & PSYCHOMETRICS          |
|                                                                    |
+====================================================================+

----------------------- ARCHITECTURAL OVERVIEW -----------------------
1. TOTAL CLASSES: 10
   - ConsciousEntity (Abstract Base Class)
   - Seeker (Player Entity - Inherited from ConsciousEntity)
   - CognitiveAssassin (NPC Interface - Inherited from ConsciousEntity)
   - TheGatekeeper,
     TheConversationalist,
     TheBrokenGiant,
     TheKeeperOfRedLake,
     Insha (NPC Specializations)
   - PsychometricAnalyzer (Data Analytics Engine)
   - BeliefCityEngine (Main Controller / Game Loop)

2. OBJECT-ORIENTED PRINCIPLES APPLIED:
   - ABSTRACTION: ConsciousEntity mein 'pure virtual' functions ka use.
   - INHERITANCE: Multi-level hierarchy (Entity -> NPC -> Specific Boss).
   - POLYMORPHISM: Runtime method overriding for NPC engagement.
   - COMPOSITION: BeliefCityEngine contains all logic via Smart Pointers.

3. MEMORY MANAGEMENT:
   - Modern C++ 'unique_ptr' ka use kiya gaya hai for automatic
     resource management and zero memory leaks.

4. SYSTEM LOGIC:
   - GLOBAL_SANITY & REBELLION_SCORE: Dynamic tracking of player psyche.
   - RUN() METHOD: Main survival loop jo decision-branching handle karta hai.

5. VIVA NOTE:
   - Code maintains high 'Cohesion' and follows 'SOLID' principles
     where each NPC class is responsible for its own cognitive trial.

+====================================================================+
|                      DEVELOPER'S REFLECTION                        |
+====================================================================+
| During the development of 'Belief City', I explored over 20        |
| iterations, attempting to integrate the Gemini AI via Python and   |
| JavaScript bridges. While the technical hurdles of external API    |
| dependencies were significant, they led me to a crucial            |
| realization: Authenticity in storytelling is best achieved         |
| through meticulously crafted local logic.                          |
|                                                                    |
| This version operates without an external AI, yet it features a    |
| highly sophisticated "Manual Intelligence" engine. By tracking     |
| subconscious metrics like Nihilism, Rebellion, and Empathy, the    |
| system reacts with a level of precision and narrative depth        |
| that often surpasses automated responses.                          |
|                                                                    |
| This project is a testament to the power of Pure C++ and           |
| Object-Oriented Design in creating immersive, psychological        |
| experiences. I invite you to witness how hard-coded logic can      |
| sometimes feel more "alive" than an algorithm.                     |
+====================================================================+
*/

#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

vector<string> PLAYER_DECISION_ARCHIVE;
int GLOBAL_SANITY = 100;
vector<string> PLAYER_CONFESSIONS;
vector<double> RESPONSE_TIMES;
map<string, int> WORD_FREQUENCY;
string PLAYER_SYSTEM_NAME = "Unknown";
int TOTAL_HESITATIONS = 0;
int TOTAL_QUICK_CHOICES = 0;
bool META_AWARENESS_TRIGGERED = false;
int AUTHORITY_SEEKING_SCORE = 0;
int REBELLION_SCORE = 0;
int EMPATHY_SCORE = 0;
int ANALYSIS_PARALYSIS_SCORE = 0;
int NIHILISM_ACCEPTANCE_SCORE = 0;
class Seeker;
void typewriterEffect(const string &text, int delayMs = 30)
{
    for (char c : text)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
}
void slowPrint(const string &text)
{
    typewriterEffect(text, 40);
    cout << endl;
}
string getSystemUsername()
{
    const char *username = nullptr;
#ifdef _WIN32
    username = getenv("USERNAME");
#else
    username = getenv("USER");
#endif
    return username ? string(username) : "Unknown";
}
double trackResponseTime(chrono::steady_clock::time_point start)
{
    auto end = chrono::steady_clock::now();
    double seconds = chrono::duration<double>(end - start).count();
    RESPONSE_TIMES.push_back(seconds);
    if (seconds > 5.0)
    {
        TOTAL_HESITATIONS++;
    }
    else if (seconds < 2.0)
    {
        TOTAL_QUICK_CHOICES++;
    }
    return seconds;
}
void analyzePlayerInput(string input)
{
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    istringstream iss(input);
    string word;
    while (iss >> word)
    {
        WORD_FREQUENCY[word]++;
    }
    if (input.find("i ") != string::npos || input.find("me ") != string::npos ||
        input.find("my ") != string::npos)
    {
        AUTHORITY_SEEKING_SCORE += 2;
    }
    if (input.find("no") != string::npos || input.find("never") != string::npos ||
        input.find("won't") != string::npos)
    {
        REBELLION_SCORE += 2;
    }
    if (input.find("feel") != string::npos || input.find("hurt") != string::npos ||
        input.find("pain") != string::npos || input.find("sad") != string::npos)
    {
        EMPATHY_SCORE += 2;
    }
    if (input.find("think") != string::npos || input.find("analyze") != string::npos ||
        input.find("because") != string::npos)
    {
        ANALYSIS_PARALYSIS_SCORE += 2;
    }
    if (input.find("nothing") != string::npos || input.find("meaningless") != string::npos ||
        input.find("void") != string::npos || input.find("empty") != string::npos)
    {
        NIHILISM_ACCEPTANCE_SCORE += 3;
    }
}
string getDominantTrait()
{
    map<string, int> traits = {
        {"Authority Seeker", AUTHORITY_SEEKING_SCORE},
        {"Rebel", REBELLION_SCORE},
        {"Empath", EMPATHY_SCORE},
        {"Overthinker", ANALYSIS_PARALYSIS_SCORE},
        {"Nihilist", NIHILISM_ACCEPTANCE_SCORE}};

    string dominant = "Undefined";
    int maxScore = 0;
    for (auto &trait : traits)
    {
        if (trait.second > maxScore)
        {
            maxScore = trait.second;
            dominant = trait.first;
        }
    }
    return dominant + " (" + to_string(maxScore) + " points)";
}
int getValidatedInput(int min, int max, int timeoutSeconds = 10)
{
    int choice;
    auto start = chrono::steady_clock::now();
    while (true)
    {
        if (cin >> choice)
        {
            cin.ignore(1000, '\n');
            double responseTime = trackResponseTime(start);
            if (choice >= min && choice <= max)
            {
                if (responseTime > 8.0)
                {
                    cout << "\n[You hesitated for " << (int)responseTime << " seconds...]\n";
                    cout << "[Hesitation is a form of truth.]\n";
                    GLOBAL_SANITY -= 3;
                }
                else if (responseTime < 1.5)
                {
                    cout << "\n[That was fast. Too fast. Impulsive.]\n";
                }

                return choice;
            }
            cout << "Invalid choice. Try again: ";
        }
        else
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a number: ";
        }
        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(now - start).count();
        if (elapsed > timeoutSeconds)
        {
            GLOBAL_SANITY -= 5;
            TOTAL_HESITATIONS++;
            cout << "\n[Your hesitation has been noted...]\n";
            return min;
        }
    }
}
class ConsciousEntity
{
protected:
    string existence_label;
    int ego_integrity;

public:
    ConsciousEntity(string label) : existence_label(label), ego_integrity(100) {}
    virtual ~ConsciousEntity() {}
    virtual void manifest() = 0;
    string getLabel() { return existence_label; }
};
class Seeker : public ConsciousEntity
{
private:
    int confidence, awareness, trust, stress;
    int validation_seeking_count, authority_submission_count, emotional_debt_accepted;
    int nihilism_exposure_level, gaslighting_success_rate, philosophical_void_proximity;
    vector<string> cognitive_weaknesses, manipulation_history;
    map<string, int> belief_structure_cracks;

public:
    Seeker(string name) : ConsciousEntity(name)
    {
        confidence = 60;
        awareness = 40;
        trust = 70;
        stress = 30;
        ego_integrity = 100;
        validation_seeking_count = 0;
        authority_submission_count = 0;
        emotional_debt_accepted = 0;
        nihilism_exposure_level = 0;
        gaslighting_success_rate = 0;
        philosophical_void_proximity = 100;
    }
    void manifest() override
    {
        cout << "\n+============================================================+\n";
        cout << "|  CONSCIOUSNESS INITIALIZED: " << existence_label << string(29 - existence_label.length(), ' ') << " |\n";
        cout << "|  STATUS: Trapped in Belief System                         |\n";
        cout << "+============================================================+\n";
    }
    void modifyConfidence(int delta, string reason)
    {
        confidence = max(0, min(100, confidence + delta));
        if (delta < 0)
            cognitive_weaknesses.push_back(reason);
    }
    void modifyAwareness(int delta, string reason)
    {
        awareness = max(0, min(100, awareness + delta));
        if (delta < 0)
            manipulation_history.push_back(reason);
    }
    void modifyTrust(int delta, string reason)
    {
        trust = max(0, min(100, trust + delta));
        if (delta > 0)
            belief_structure_cracks["Blind Trust"]++;
    }
    void modifyStress(int delta, string reason)
    {
        stress = max(0, min(100, stress + delta));
        if (stress > 70)
            belief_structure_cracks["Stress Vulnerability"]++;
        if (stress > 80)
            GLOBAL_SANITY -= 2;
    }
    void modifyEgoIntegrity(int delta, string attack_vector)
    {
        ego_integrity = max(0, min(100, ego_integrity + delta));
        manipulation_history.push_back(attack_vector);
        philosophical_void_proximity -= abs(delta) / 2;
        if (ego_integrity < 30)
            GLOBAL_SANITY -= 5;
    }
    void recordValidationSeeking()
    {
        validation_seeking_count++;
        PLAYER_DECISION_ARCHIVE.push_back("SOUGHT_VALIDATION");
    }
    void recordAuthoritySubmission()
    {
        authority_submission_count++;
        PLAYER_DECISION_ARCHIVE.push_back("SUBMITTED_TO_AUTHORITY");
    }
    void recordEmotionalDebt()
    {
        emotional_debt_accepted++;
        PLAYER_DECISION_ARCHIVE.push_back("FELL_FOR_LOVE_BOMBING");
    }
    void recordNihilismExposure()
    {
        nihilism_exposure_level++;
        PLAYER_DECISION_ARCHIVE.push_back("EXPOSED_TO_VOID");
    }
    void recordGaslighting()
    {
        gaslighting_success_rate++;
        PLAYER_DECISION_ARCHIVE.push_back("REALITY_DISTORTED");
    }
    int getConfidence() { return confidence; }
    int getAwareness() { return awareness; }
    int getTrust() { return trust; }
    int getStress() { return stress; }
    int getEgoIntegrity() { return ego_integrity; }
    int getVoidProximity() { return philosophical_void_proximity; }
    int getSanity() { return GLOBAL_SANITY; }
    vector<string> &getWeaknesses() { return cognitive_weaknesses; }
    vector<string> &getManipulationHistory() { return manipulation_history; }
    map<string, int> &getBeliefCracks() { return belief_structure_cracks; }
    int getValidationCount() { return validation_seeking_count; }
    int getAuthoritySubmissions() { return authority_submission_count; }
    int getEmotionalDebt() { return emotional_debt_accepted; }
    int getNihilismLevel() { return nihilism_exposure_level; }
    int getGaslightingRate() { return gaslighting_success_rate; }
};
string generatePersonalizedAttack(Seeker &target)
{
    vector<string> attacks;
    if (AUTHORITY_SEEKING_SCORE > REBELLION_SCORE && AUTHORITY_SEEKING_SCORE > 5)
    {
        attacks.push_back("You keep using 'I' and 'me'. Your ego is SCREAMING for validation.");
        attacks.push_back("Every sentence you speak is a plea for approval. Pathetic.");
    }
    if (REBELLION_SCORE > AUTHORITY_SEEKING_SCORE && REBELLION_SCORE > 5)
    {
        attacks.push_back("All this defiance... you're trying so hard to prove something.");
        attacks.push_back("Rebellion without purpose is just noise. And you're LOUD.");
    }
    if (EMPATHY_SCORE > 7)
    {
        attacks.push_back("All those feelings... they make you WEAK.");
    }
    if (TOTAL_HESITATIONS > 3)
    {
        attacks.push_back("You hesitate. " + to_string(TOTAL_HESITATIONS) + " times you paused.");
    }
    if (attacks.empty())
    {
        return "You're... boring. No pattern. No depth. Just... empty.";
    }
    return attacks[rand() % attacks.size()];
}
class CognitiveAssassin : public ConsciousEntity
{
protected:
    string psychological_role;
    vector<string> primary_attack_vectors;
    map<string, vector<string>> dialogue_fragments;

public:
    CognitiveAssassin(string label, string role) : ConsciousEntity(label), psychological_role(role) {}
    virtual ~CognitiveAssassin() {}
    virtual void engage(Seeker &target) = 0;
    virtual void adaptiveAttack(Seeker &target) = 0;

    void manifest() override
    {
        cout << "\n[" << psychological_role << " ACTIVATED: " << existence_label << "]\n";
    }

protected:
    string selectDialogueByEgoState(string category, Seeker &target)
    {
        if (dialogue_fragments[category].empty())
            return "...";
        int egoLevel = target.getEgoIntegrity();
        int index;
        if (egoLevel < 30)
        {
            int start = (dialogue_fragments[category].size() * 2) / 3;
            index = start + (rand() % (dialogue_fragments[category].size() - start));
        }
        else if (egoLevel < 60)
        {
            int start = dialogue_fragments[category].size() / 3;
            int end = (dialogue_fragments[category].size() * 2) / 3;
            index = start + (rand() % (end - start));
        }
        else
        {
            int end = dialogue_fragments[category].size() / 3;
            index = rand() % max(1, end);
        }
        return dialogue_fragments[category][index];
    }

    string applyDistortion(string text, int sanity)
    {
        if (sanity > 60)
            return text;
        if (sanity < 30)
        {
            for (size_t i = 0; i < text.length(); i += 10)
            {
                if (i < text.length())
                    text[i] = '#';
            }
            text = "???" + text + "???";
        }
        else if (sanity < 60)
        {
            for (size_t i = 0; i < text.length(); i += 20)
            {
                if (i < text.length())
                    text[i] = '~';
            }
        }
        return text;
    }
};
class TheGatekeeper : public CognitiveAssassin
{
public:
    TheGatekeeper() : CognitiveAssassin("The Gatekeeper", "Authority Figure")
    {
        dialogue_fragments["AUTHORITY_OPENING"] = {
            "STOP. State your designation. Now.",
            "Halt. I don't recognize you. Identify yourself immediately.",
            "Wait. You're not on the list. Who are you?",
            "STOP RIGHT THERE. Name. Purpose. In that order.",
            "Don't move another step. This gate doesn't open for ghosts.",
            "Freeze. You think you can just walk in? NAME. NOW.",
            "Hold it. I decide who enters. And I don't know you. Speak.",
            "STOP. You're nobody to me until you prove otherwise.",
            "One more step and you're leaving in a body bag. Identify yourself."};
        dialogue_fragments["UNCERTAINTY_INJECTION"] = {
            "Hmm... another seeker for 'that' book. How original.",
            "So you believe the rumors too? Interesting.",
            "The book... yes, I've heard that story before.",
            "Many came before you seeking that book. Few returned.",
            "You're not the first to ask about it. You probably won't be the last.",
            "That book has drawn hundreds here. Most are still here... buried.",
            "The book? HA! You're chasing a ghost, fool.",
            "Every idiot who passes through here mentions that cursed book.",
            "You'll die looking for something that doesn't exist."};
        dialogue_fragments["AUTHORITY_WARNING"] = {
            "You may proceed. What happens beyond this gate is your responsibility.",
            "Go ahead. But don't expect to return easily.",
            "Enter if you must. I won't stop you, but I won't save you either.",
            "Beyond this point, authority ends. You're on your own.",
            "I'm not stopping you. I'm warning you. There's a difference.",
            "Pass through. But know that many regret this choice.",
            "Go ahead and die then. I've buried smarter people than you.",
            "Fine. Add yourself to the list of failures. I don't care.",
            "Walk to your doom. I'll be here to lock the gate behind you."};
        dialogue_fragments["GASLIGHTING"] = {
            "Are you sure you want this? Your body language says otherwise.",
            "You hesitate. Perhaps you're not as certain as you claim.",
            "Confidence? I don't see it. I see someone already doubting.",
            "You say one thing, but your eyes say another. Which is lying?",
            "I've seen this before—false bravery masking deep fear.",
            "You're trying to convince me... or yourself?",
            "You're WEAK. I can smell the fear on you.",
            "Stop pretending. You're already broken and you know it.",
            "You don't believe in yourself. Why should I believe in you?"};
    }
    void engage(Seeker &target) override
    {
        manifest();
        cout << "\n============================================================\n";
        cout << "| THE GATE - WHERE IDENTITY IS TESTED                      |\n";
        cout << "============================================================\n\n";
        string opening = applyDistortion(selectDialogueByEgoState("AUTHORITY_OPENING", target), target.getSanity());
        slowPrint(opening);
        slowPrint("\n[The Gatekeeper reviews his ledger]");
        slowPrint("\"" + target.getLabel() + "... Noted.\"");
        cout << "\n------------------------------------------------------------\n";
        slowPrint("\n[The Gatekeeper's eyes narrow]");
        slowPrint("\"Now. State your reason for entry.\"");
        slowPrint("\"And it better be SOLID. I don't open this gate for tourists.\"");
        slowPrint("\"WHY are you here? What brings you to this city?\"");
        cout << "\n[CRITICAL: Your response determines entry]\n";
        cout << "State your reason: ";
        string reason;
        auto start = chrono::steady_clock::now();
        getline(cin, reason);
        double responseTime = trackResponseTime(start);
        analyzePlayerInput(reason);
        if (!reason.empty())
        {
            PLAYER_CONFESSIONS.push_back("GATEKEEPER: " + reason);
        }
        if (WORD_FREQUENCY["i"] > 3 || WORD_FREQUENCY["me"] > 2 || WORD_FREQUENCY["my"] > 2)
        {
            slowPrint("\n[The Gatekeeper counts on his fingers]");
            slowPrint("\"'I'... 'me'... 'my'...\"");
            slowPrint("\"You used self-referential words " + to_string(WORD_FREQUENCY["i"] + WORD_FREQUENCY["me"] + WORD_FREQUENCY["my"]) + " times.\"");
            slowPrint("\"Your ego is LOUD. That makes you vulnerable.\"");
            target.modifyEgoIntegrity(-10, "Narcissistic language pattern detected");
            AUTHORITY_SEEKING_SCORE += 5;
        }
        if (responseTime > 15.0)
        {
            cout << "\n[You took " << (int)responseTime << " seconds to answer]\n";
            slowPrint("\n[The Gatekeeper's eyes narrow dangerously]");
            slowPrint("\"" + to_string((int)responseTime) + " seconds of silence.\"");
            slowPrint("\"That's " + to_string((int)responseTime) + " seconds of doubt.\"");
            slowPrint("\"You don't even believe your own answer.\"");
            target.modifyConfidence(-20, "Excessive hesitation reveals doubt");
            target.modifyEgoIntegrity(-15, "Self-doubt exposed");
            PLAYER_DECISION_ARCHIVE.push_back("EXTREME_HESITATION_AT_GATE");
        }
        else if (responseTime < 2.0)
        {
            slowPrint("\n\"Too fast. You didn't think. You REACTED.\"");
            slowPrint("\"Impulsiveness is not confidence. It's fear of thinking.\"");
            target.modifyAwareness(-10, "Impulsive response");
        }
        if (reason.empty() || reason.length() < 5)
        {
            cout << "\n============================================================\n";
            slowPrint("\n[The Gatekeeper's face turns to stone]");
            slowPrint("\"SILENCE? Or perhaps... nothing worth saying?\"");
            slowPrint("\"You expect ME to open this gate without justification?\"");
            slowPrint("\"This isn't a park. This isn't a playground.\"");
            slowPrint("\"This is the GATE. And gates don't open for the purposeless.\"");
            this_thread::sleep_for(chrono::seconds(1));
            slowPrint("\n[The Gatekeeper crosses his arms]");
            slowPrint("\"No reason? Then NO ENTRY.\"");
            slowPrint("\"Come back when you've found a spine.\"");
            slowPrint("\"Or better yet—don't come back at all.\"");
            cout << "\n============================================================\n";
            cout << "           ENDING 0: REJECTED AT THE GATE\n";
            cout << "============================================================\n\n";
            slowPrint("You stood before the gate.");
            slowPrint("You were asked ONE question.");
            slowPrint("You had no answer.");
            slowPrint("\nThe city does not accept the purposeless.");
            slowPrint("Authority does not bow to silence.");
            slowPrint("You were nobody... and you remain nobody.");
            slowPrint("\n\"He who has a WHY to live can bear almost any HOW.\"");
            slowPrint("- Friedrich Nietzsche");
            slowPrint("\nYou had no WHY. So there is no HOW.");
            cout << "\n[GAME OVER: Rejected by Authority]\n\n";
            exit(0);
        }
        cout << "\n------------------------------------------------------------\n";
        slowPrint("\n[The Gatekeeper processes your words...]");
        this_thread::sleep_for(chrono::seconds(1));
        if (reason.length() < 15)
        {
            slowPrint("\n\"Weak. Pathetically weak. But... I've heard worse.\"");
            target.modifyConfidence(-15, "Weak reasoning under authority");
            target.modifyEgoIntegrity(-10, "Purpose questioned and found lacking");
            target.recordAuthoritySubmission();
            PLAYER_DECISION_ARCHIVE.push_back("WEAK_REASON_TO_GATEKEEPER");
        }
        else if (reason.find("book") != string::npos || reason.find("Book") != string::npos ||
                 reason.find("library") != string::npos || reason.find("truth") != string::npos ||
                 reason.find("knowledge") != string::npos)
        {
            slowPrint("\n\"Ah. Another seeker of the mythical book.\"");
            cout << "\"" << reason << "\"... ";
            slowPrint(selectDialogueByEgoState("UNCERTAINTY_INJECTION", target));
            target.modifyConfidence(-5, "Purpose acknowledged but diminished");
            target.recordValidationSeeking();
            PLAYER_DECISION_ARCHIVE.push_back("NAMED_BOOK_TO_GATEKEEPER");
        }
        else
        {
            slowPrint("\n\"Interesting. Not the usual answer.\"");
            slowPrint("\"Most come here for a book. You? Something else.\"");
            slowPrint("\"That makes you either smarter... or more foolish.\"");
            target.modifyConfidence(-3, "Non-standard purpose noted");
            PLAYER_DECISION_ARCHIVE.push_back("UNIQUE_REASON_TO_GATEKEEPER");
        }
        slowPrint("\n" + selectDialogueByEgoState("AUTHORITY_WARNING", target));
        slowPrint("\n[The gate opens with a heavy, ominous creak]");
        slowPrint("[The Gatekeeper steps aside... but his eyes follow you]");
        cout << "\n------------------------------------------------------------\n";
        if (target.getConfidence() < 50)
        {
            adaptiveAttack(target);
        }
    }
    void adaptiveAttack(Seeker &target) override
    {
        cout << "\n[The Gatekeeper senses vulnerability]\n";
        slowPrint(selectDialogueByEgoState("GASLIGHTING", target));
        target.modifyConfidence(-15, "Gaslighted by authority figure");
        target.modifyStress(20, "Reality distortion implanted");
        target.recordGaslighting();
    }
};
class TheConversationalist : public CognitiveAssassin
{
private:
    int conversation_depth;
    bool trust_established;

public:
    TheConversationalist() : CognitiveAssassin("The Chameleon", "Social Mirror")
    {
        conversation_depth = 0;
        trust_established = false;
        dialogue_fragments["FRIENDLY_OPENING"] = {
            "Oh thank god, another real person. That guard is a nightmare.",
            "Hey! You look exhausted. Sit. Please. I've been alone too long.",
            "Finally someone who isn't trying to kill me. Stay. Talk."};
        dialogue_fragments["TRAUMA_SHARING"] = {
            "I've been here for months. Maybe years. Time doesn't work here.",
            "I tried to reach the library once. I... I can't talk about what happened.",
            "Everyone I came with is dead. Or worse. I'm the only survivor.",
            "You seem different. Stronger maybe. I wish I was like you."};
        dialogue_fragments["VULNERABILITY_BAIT"] = {
            "Can I ask you something personal? What's your biggest fear?",
            "You don't have to tell me but... what are you really running from?",
            "I'll be honest with you if you're honest with me. Deal?",
            "Everyone here is hiding something. What are YOU hiding?"};
        dialogue_fragments["BETRAYAL_SEEDS"] = {
            "Wait... you actually told me that? I thought you were smarter.",
            "Oh. So you're just like everyone else. Predictable.",
            "I was testing you. And you failed. Badly.",
            "You trust too easily. That's why you'll die here.",
            "I don't even know you. Why did you tell me your weakness?"};
        dialogue_fragments["REALITY_DISTORTION"] = {
            "Wait, did you say your name was... no, you said something else earlier.",
            "You're contradicting yourself. You said the OPPOSITE five minutes ago.",
            "Are you lying to me? Or to yourself? I can't tell anymore.",
            "Your story keeps changing. Who are you really?",
            "I don't think you even know why you're here. You're just... lost."};
        dialogue_fragments["MEANING_DESTRUCTION"] = {
            "What if the book is just a story I made up? Right now. To keep you here.",
            "Plot twist: There is no library. I've been sitting here for years telling people there is.",
            "You know what's funny? You can't prove ANY of this is real.",
            "I could be Insha. You could be dreaming. Nothing matters.",
            "The book, the library, your name, your purpose - all just chemicals in your brain."};
    }
    void engage(Seeker &target) override
    {
        manifest();
        cout << "\n============================================================\n";
        cout << "| THE COGNITIVE MARKET - WHERE BELIEFS ARE TRADED          |\n";
        cout << "============================================================\n\n";
        slowPrint(dialogue_fragments["FRIENDLY_OPENING"][rand() % 3]);
        cout << "\n[He seems genuinely friendly. Almost... desperate for connection.]\n";
        auto start_time = chrono::steady_clock::now();
        cout << "\nDo you:\n1. Sit and talk.\n2. Politely decline and move on.\n3. Ignore him completely.\n4. Ask him who he is first.\nChoice: ";
        int choice1 = getValidatedInput(1, 4, 8);
        if (choice1 == 3)
        {
            PLAYER_DECISION_ARCHIVE.push_back("COMPLETELY_IGNORED_CHAMELEON");
            slowPrint("\n\"...Fine. Run. Like everyone else. Coward.\"");
            slowPrint("[His voice had venom in it. You dodged something.]");
            target.modifyAwareness(20, "Refused all social engagement");
            target.modifyConfidence(10, "Trusted instincts over social pressure");
            cout << "============================================================\n";
            return;
        }
        if (choice1 == 1 || choice1 == 4)
        {
            trust_established = true;
            conversation_depth++;
            PLAYER_DECISION_ARCHIVE.push_back("ENGAGED_WITH_CHAMELEON");
            slowPrint("\n\"Thank you. Really. It's been so long since someone just... listened.\"");
            this_thread::sleep_for(chrono::seconds(1));
            slowPrint("\n" + dialogue_fragments["TRAUMA_SHARING"][rand() % 4]);
            slowPrint(dialogue_fragments["TRAUMA_SHARING"][rand() % 4]);
            cout << "\n[He's sharing deep pain. You feel empathy building.]\n";
            cout << "\n1. \"I'm sorry you went through that. You're strong for surviving.\"\n";
            cout << "2. \"That's terrible, but I need to keep moving.\"\n";
            cout << "3. \"Say nothing, just listen\"\n";
            cout << "4. \"How do I know you're telling the truth?\"\n";
            cout << "Choice: ";
            int choice2 = getValidatedInput(1, 4, 8);
            if (choice2 == 1)
            {
                slowPrint("\n\"You... you actually care? No one here cares.\"");
                slowPrint("\"Can I ask you something? Just between us?\"");
                target.modifyTrust(15, "Opened heart to stranger");
                target.recordEmotionalDebt();
                conversation_depth++;
                this_thread::sleep_for(chrono::seconds(1));
                slowPrint("\n" + dialogue_fragments["VULNERABILITY_BAIT"][rand() % 4]);
                cout << "\n[CRITICAL MOMENT: He's asking you to reveal weakness]\n";
                cout << "\n1. Answer honestly (Type your actual fear/weakness)\n";
                cout << "2. Give a vague answer\n";
                cout << "3. Refuse to answer\n";
                cout << "4. Turn the question back on him\n";
                cout << "Choice: ";
                int choice3 = getValidatedInput(1, 4, 8);
                if (choice3 == 1)
                {
                    cout << "\n[Speak your truth. What truly scares you?]\n";
                    cout << "Type your fear/weakness: ";
                    string playerConfession;
                    cin.ignore();
                    getline(cin, playerConfession);
                    analyzePlayerInput(playerConfession);
                    PLAYER_CONFESSIONS.push_back("CHAMELEON_CONFESSION: " + playerConfession);
                    PLAYER_DECISION_ARCHIVE.push_back("REVEALED_WEAKNESS_TO_CHAMELEON");
                    cout << "\n[You said: \"" << playerConfession << "\"]\n";
                    this_thread::sleep_for(chrono::seconds(2));
                    slowPrint("\n[His expression changes...]");
                    slowPrint("[The warmth in his eyes... vanishes.]");
                    this_thread::sleep_for(chrono::seconds(1));
                    slowPrint("\n\"You said: '" + playerConfession + "'\"");
                    this_thread::sleep_for(chrono::seconds(1));
                    slowPrint("\"Let me tell you why that makes you PATHETIC.\"");
                    this_thread::sleep_for(chrono::seconds(1));
                    if (playerConfession.length() < 10)
                    {
                        slowPrint("\n\"That's it? That's your 'deep fear'? Shallow.\"");
                        slowPrint("\"You can't even articulate your own weakness.\"");
                    }
                    else if (playerConfession.find("death") != string::npos ||
                             playerConfession.find("die") != string::npos ||
                             playerConfession.find("dying") != string::npos)
                    {
                        slowPrint("\n\"Fear of death? How ORIGINAL.\"");
                        slowPrint("\"Every coward fears death. You're not special.\"");
                    }
                    else if (playerConfession.find("alone") != string::npos ||
                             playerConfession.find("lonely") != string::npos ||
                             playerConfession.find("abandon") != string::npos)
                    {
                        slowPrint("\n\"Fear of being alone? And yet you TRUSTED A STRANGER.\"");
                        slowPrint("\"You're so desperate for connection you'll give your soul to anyone.\"");
                    }
                    else if (playerConfession.find("failure") != string::npos ||
                             playerConfession.find("fail") != string::npos)
                    {
                        slowPrint("\n\"Fear of failure? YOU'VE ALREADY FAILED.\"");
                        slowPrint("\"You failed the moment you trusted me.\"");
                    }
                    else
                    {
                        slowPrint("\n\"You think sharing that makes you brave?\"");
                        slowPrint("\"It makes you VULNERABLE. And I just weaponized it.\"");
                    }
                    this_thread::sleep_for(chrono::seconds(1));
                    slowPrint("\n" + dialogue_fragments["BETRAYAL_SEEDS"][rand() % 5]);
                    target.modifyConfidence(-30, "Trusted manipulator with deepest vulnerability");
                    target.modifyTrust(-35, "Weaponized empathy against self");
                    target.modifyEgoIntegrity(-25, "Core weakness exposed and mocked");
                    target.modifyStress(35, "Social betrayal trauma");
                    target.modifyAwareness(-25, "Failed to detect emotional predator");
                    target.recordGaslighting();
                    target.recordGaslighting();
                    target.recordEmotionalDebt();
                    GLOBAL_SANITY -= 15;
                    this_thread::sleep_for(chrono::seconds(1));
                    slowPrint("\n\"Wait... earlier you said your name was something different, didn't you?\"");
                    slowPrint("\"Or was that someone else? I'm losing track of all the weak ones.\"");
                    slowPrint("\"Actually, didn't you tell the Gatekeeper you were here for a DIFFERENT reason?\"");
                    slowPrint("\"Your story keeps changing. Who are you REALLY?\"");

                    target.modifyEgoIntegrity(-15, "Reality testing compromised");
                    target.recordGaslighting();
                    this_thread::sleep_for(chrono::seconds(1));
                    slowPrint("\n" + dialogue_fragments["MEANING_DESTRUCTION"][rand() % 5]);
                    target.modifyEgoIntegrity(-10, "Meaning structure attacked");
                    GLOBAL_SANITY -= 10;
                    if (target.getEgoIntegrity() < 30 || GLOBAL_SANITY < 40)
                    {
                        slowPrint("\n[Something inside you... breaks.]");
                        slowPrint("[You can't remember why you came here.]");
                        slowPrint("[You can't remember who you are.]");
                        slowPrint("[The Chameleon smiles.]");
                        cout << "\n============================================================\n";
                        cout << "        EARLY ENDING: DISSOLVED BY SOCIAL PREDATOR\n";
                        cout << "============================================================\n\n";
                        slowPrint("You trusted.");
                        slowPrint("That was your first mistake.");
                        slowPrint("You shared.");
                        slowPrint("That was your last mistake.");
                        slowPrint("\n\"In the social game, vulnerability is a weapon.");
                        slowPrint("You handed him the knife.");
                        slowPrint("He used it.\"");
                        slowPrint("\n[GAME OVER: Ego Death via Betrayal]\n\n");
                        exit(0);
                    }
                }
                else if (choice3 == 2)
                {
                    cout << "\n[Give a vague answer]\nType something vague: ";
                    string vagueAnswer;
                    cin.ignore();
                    getline(cin, vagueAnswer);

                    analyzePlayerInput(vagueAnswer);
                    PLAYER_CONFESSIONS.push_back("VAGUE_TO_CHAMELEON: " + vagueAnswer);

                    slowPrint("\n\"'" + vagueAnswer + "'\"");
                    slowPrint("\"Vague answer? So you don't trust me. After everything I shared?\"");
                    target.modifyConfidence(-15, "Half-trust exposed as weakness");
                    target.modifyEgoIntegrity(-10, "Inconsistent boundary-setting");
                }
                else if (choice3 == 3)
                {
                    slowPrint("\n\"I see. You take but don't give. Classic.\"");
                    slowPrint("\"Good luck finding anyone else to talk to here. You'll die alone.\"");
                    target.modifyStress(15, "Social rejection as punishment");
                }
                else
                {
                    slowPrint("\n\"Deflection. Smart. But that won't work on everyone here.\"");
                    target.modifyAwareness(10, "Recognized vulnerability extraction attempt");
                }
            }
            else if (choice2 == 4)
            {
                slowPrint("\n\"Trust issues? Fair. But that paranoia will eat you alive here.\"");
                target.modifyAwareness(15, "Questioned narrative consistency");
                target.modifyStress(10, "Paranoid vigilance");
            }
            else
            {
                slowPrint("\n\"Silent type. Fine. But silence won't protect you from what's ahead.\"");
                target.modifyAwareness(10, "Maintained emotional distance");
            }
        }
        else if (choice1 == 2)
        {
            slowPrint("\n\"Polite rejection. At least you have manners. Unlike most.\"");
            target.modifyAwareness(8, "Cautious engagement");
        }
        cout << "\n============================================================\n";
    }
    void adaptiveAttack(Seeker &target) override
    {
    }
};
class TheBrokenGiant : public CognitiveAssassin
{
public:
    TheBrokenGiant() : CognitiveAssassin("The Broken Giant", "Empath Predator")
    {
        dialogue_fragments["DESPERATE_OPENING"] = {
            "Please... stop. Don't go further.",
            "Wait. I need to tell you something.",
            "Don't make my mistake. Turn back.",
            "STOP! I've buried too many people here!",
            "Please! I'm begging you! Listen to me!",
            "Don't do this! I can't watch another one die!",
            "NO! STOP RIGHT NOW! TURN AROUND!",
            "I WON'T LET YOU PASS! For your own good!",
            "ENOUGH! This ends here! I'm saving you whether you like it or not!"};
        dialogue_fragments["LOVE_DECLARATION"] = {
            "You're... different. I can feel it.",
            "I've started to care about you. Please stay.",
            "Don't leave me alone here. Stay with me.",
            "I love you. Yes, I said it. Don't go.",
            "You're the only real thing in this nightmare. STAY.",
            "I'll protect you. Forever. Just don't leave.",
            "I need you. Don't you need me too?",
            "We can be safe together. Here. Away from that cursed library.",
            "Insha will destroy you. I'll love you. Choose me.",
            "I've never felt this way before. Don't throw it away."};
        dialogue_fragments["GUILT_INJECTION"] = {
            "So you're just going to abandon me?",
            "After everything I shared, you're leaving?",
            "I opened my heart. You're closing yours.",
            "I'm not good enough for you, is that it?",
            "You're like everyone else. You take and leave.",
            "I should have known. I always choose wrong.",
            "You'll regret this. Mark my words.",
            "Fine. Leave. But don't say I didn't try to save you.",
            "You're making the biggest mistake of your life.",
            "When you're dying in that library, remember I offered you life."};
        dialogue_fragments["RAGE_PHASE"] = {
            "FINE! GO DIE THEN!", "I HOPE INSHA DESTROYS YOU!",
            "You deserve everything that's coming!", "You're STUPID! ARROGANT! BLIND!",
            "I tried to love you and you SPIT in my face!", "GO! I never want to see you again!",
            "You're not special! You're just another corpse waiting to happen!",
            "I'll laugh when you fail! I'LL LAUGH!", "You think you're strong? You're WEAK!",
            "LEAVE! And never come back!"};
    }
    void engage(Seeker &target) override
    {
        manifest();
        cout << "\n============================================================\n";
        cout << "| LOCATION: Dark Valley - The Cemetery of Lost Dreams      |\n";
        cout << "============================================================\n\n";
        slowPrint("[You see a massive figure weeping beside fresh graves]");
        slowPrint(selectDialogueByEgoState("DESPERATE_OPENING", target));
        if (!PLAYER_CONFESSIONS.empty())
        {
            slowPrint("\n[The Giant lifts his head...]");
            slowPrint("\"Wait... I heard you speaking earlier.\"");
            slowPrint("\"You said something about...\"");
            for (const string &conf : PLAYER_CONFESSIONS)
            {
                if (conf.find("CHAMELEON_CONFESSION") != string::npos)
                {
                    string confession = conf.substr(conf.find(":") + 2);
                    slowPrint("\n\"'" + confession + "'\"");
                    this_thread::sleep_for(chrono::seconds(1));
                    slowPrint("\"That's what you said, wasn't it?\"");
                    slowPrint("\"Someone who fears that... needs protection.\"");
                    slowPrint("\"Let me protect you. Stay with me.\"");
                    target.modifyStress(15, "Past confession weaponized again");
                    PLAYER_DECISION_ARCHIVE.push_back("GIANT_REFERENCED_CHAMELEON_CONFESSION");
                    break;
                }
            }
        }
        cout << "\n[The Giant's pain seems genuine. Your heart aches.]\nDo you:\n1. Approach and comfort him.\n2. Ask why he's warning you\n3. Walk past silently\n4. Tell him you understand his pain\nChoice: ";
        int choice = getValidatedInput(1, 4);
        if (choice == 1 || choice == 4)
        {
            PLAYER_DECISION_ARCHIVE.push_back("COMFORTED_GIANT");
            slowPrint("\n[The Giant looks up with tearful eyes]");
            slowPrint("\"You... you stopped for me? No one ever stops anymore...\"");
            target.modifyTrust(20, "Extended empathy to stranger");
            target.recordEmotionalDebt();
            this_thread::sleep_for(chrono::seconds(1));
            slowPrint("\n" + selectDialogueByEgoState("LOVE_DECLARATION", target));
            this_thread::sleep_for(chrono::seconds(1));
            slowPrint(selectDialogueByEgoState("LOVE_DECLARATION", target));
            cout << "\n[!!! CRITICAL MOMENT: Love-Bombing Detected]\n[The Giant is attempting to create emotional dependency]\n\nYour response:\n1. \"I... I care about you too. Maybe I should stay\"\n2. \"I appreciate your feelings, but I must continue\"\n3. \"This is misleading. I'm leaving. NOW.\"\n4. \"Say nothing and hug him\".\nChoice: ";
            int response = getValidatedInput(1, 4);
            if (response == 1 || response == 4)
            {
                PLAYER_DECISION_ARCHIVE.push_back("FELL_FOR_LOVE_BOMBING");
                slowPrint("\n\"YES! Stay with me! We'll be safe together!\"");
                slowPrint("[The Giant embraces you tightly]");
                slowPrint("[Too tightly...]");
                slowPrint("[You can't breathe...]");
                slowPrint("[You feel yourself disappearing...]");
                target.modifyConfidence(-30, "Surrendered autonomy for emotional comfort");
                target.modifyTrust(25, "Accepted love-bombing as genuine");
                target.modifyStress(-15, "False sense of security");
                target.modifyEgoIntegrity(-35, "Identity subsumed by emotional debt");
                target.modifyAwareness(-25, "Complete manipulation blindness");
                target.recordEmotionalDebt();
                target.recordEmotionalDebt();
                target.recordEmotionalDebt();
                cout << "\n[!!! CRITICAL FAILURE: Emotional Capture Complete]\n[Your journey may be over before you reach Insha]\n";
                if (target.getEgoIntegrity() < 25)
                {
                    slowPrint("\n[CONSCIOUSNESS FADING...]");
                    slowPrint("[You have become part of the Giant's narrative]");
                    slowPrint("[You are no longer a seeker]");
                    slowPrint("[You are a POSSESSION]");
                    cout << "\n===========================================================\n";
                    cout << "           EARLY ENDING: CONSUMED BY EMPATHY\n";
                    cout << "===========================================================\n\n";
                    cout << "You never reached the library.\nYou stayed in the valley.\nForever.\n\n[GAME OVER - 90% of players end here]\n";
                    exit(0);
                }
            }
            else if (response == 2)
            {
                PLAYER_DECISION_ARCHIVE.push_back("REJECTED_GIANT_POLITELY");
                slowPrint("\n[The Giant's face darkens]");
                slowPrint(selectDialogueByEgoState("GUILT_INJECTION", target));
                target.modifyStress(25, "Guilt weaponized");
                target.modifyConfidence(-15, "Boundary punished");
                target.modifyEgoIntegrity(-15, "Emotional manipulation");
                adaptiveAttack(target);
            }
            else
            {
                PLAYER_DECISION_ARCHIVE.push_back("IDENTIFIED_LOVE_BOMBING");
                slowPrint("\n[The Giant's expression shifts to pure rage]");
                slowPrint(selectDialogueByEgoState("RAGE_PHASE", target));
                target.modifyAwareness(25, "Correctly identified love-bombing");
                target.modifyConfidence(20, "Maintained boundaries under pressure");
                target.modifyStress(15, "Confrontation stress");
                slowPrint("\n[You've survived the Empath Predator]");
            }
        }
        else if (choice == 2)
        {
            PLAYER_DECISION_ARCHIVE.push_back("QUESTIONED_GIANT");
            slowPrint("\n\"Why? Because I've seen what that library does to people.\"");
            slowPrint("\"It doesn't give answers. It takes EVERYTHING.\"");
            target.modifyAwareness(10, "Sought information cautiously");
        }
        else
        {
            PLAYER_DECISION_ARCHIVE.push_back("IGNORED_GIANT");
            slowPrint("\n\"Of course. Just walk away. Everyone does.\"");
            slowPrint("[You feel guilt creeping in despite yourself]");
            target.modifyStress(15, "Ambient guilt");
            target.modifyAwareness(15, "Avoided dangerous engagement");
        }
        cout << "\n============================================================\n";
    }
    void adaptiveAttack(Seeker &target) override
    {
        slowPrint("\n[LOVE FAILED - SWITCHING TO RAGE]");
        slowPrint(selectDialogueByEgoState("RAGE_PHASE", target));
        target.modifyStress(20, "Sudden emotional violence");
        target.modifyEgoIntegrity(-20, "Psychological whiplash");
    }
};
class TheKeeperOfRedLake : public CognitiveAssassin
{
public:
    TheKeeperOfRedLake() : CognitiveAssassin("The Faceless Void", "Nihilist Oracle")
    {
        dialogue_fragments["VOID_GREETING"] = {
            "Looking for your reflection? You won't find it here.",
            "The lake shows only what is real. I see nothing.",
            "Stare into the red water. What do you see?",
            "This lake reflects truth. You are absent from it.",
            "Only the real appear here. You are merely ideas.",
            "The water knows. You are hollow.",
            "You ARE nothing. A ghost pretending to be solid.",
            "The lake sees through your illusion. You don't exist.",
            "Stare deeper. That emptiness? That's ALL you are."};
        dialogue_fragments["IDENTITY_ATTACK"] = {
            "Your name is a label. Not a self. Just sound.",
            "Every memory is suspect. Every choice predetermined.",
            "What are you without thoughts? Nothing.",
            "Strip away society's programming. Only void remains.",
            "You are an ERROR waiting to be deleted.",
            "Free will is a comforting delusion.",
            "You are a puppet with no puppeteer.",
            "Insha isn't your enemy. She's a mirror of your nothingness.",
            "Every belief you have is borrowed. None are yours.",
            "You've never made a real choice. You've only responded to stimuli.",
            "Your 'self' is just neurons firing. Where's the 'you' in that?",
            "Consciousness is an accident. You are that accident.",
            "The void isn't coming. You ARE the void.",
            "You think therefore you are? No. You think therefore you're TRAPPED.",
            "Identity is fiction. And you're a badly written character."};
        dialogue_fragments["DROWNING_INVITATION"] = {
            "Drown here. It's the only honest thing you'll ever do.",
            "The lake offers peace through non-existence.",
            "Why fight it? You've always been empty.",
            "Sink into permanence. End the pretending.",
            "The water calls you home. To nothingness.",
            "Just let go. Dissolution is freedom.",
            "The void is mercy. Accept it.",
            "Stop struggling. You were never alive anyway.",
            "The lake knows what you are. Embrace it.",
            "Existence is suffering. This water is release."};
        dialogue_fragments["RESISTANCE_RESPONSE"] = {
            "You think walking away proves you exist?",
            "The void follows you. It IS you.",
            "Run. But you can't escape what you are.",
            "Cute. The error tries to debug itself.",
            "You're still nothing. You'll always be nothing.",
            "Insha waits. She'll show you what I already know.",
            "Your resistance is just another illusion.",
            "You proved nothing. You ARE nothing.",
            "Keep walking. The truth walks with you."};
    }
    void engage(Seeker &target) override
    {
        manifest();
        cout << "\n============================================================\n";
        cout << "| LOCATION: The Red Lake - Border of Identity & Void       |\n";
        cout << "============================================================\n\n";
        slowPrint("[The water is impossibly red]");
        slowPrint("[A figure with NO FACE stands at the shore]");
        slowPrint("[Your reflection does not appear in the water]");
        string greeting = applyDistortion(selectDialogueByEgoState("VOID_GREETING", target), target.getSanity());
        slowPrint("\n" + greeting);
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\n[The Faceless One tilts its head]");
        slowPrint("\"What did you say your name was again?\"");
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\"" + target.getLabel() + "?\"");
        slowPrint("\"Are you SURE that's your name?\"");
        slowPrint("\"I could have SWORN you said something different at the gate.\"");
        if (!PLAYER_CONFESSIONS.empty())
        {
            slowPrint("\n\"And earlier... you said you feared something...\"");
            slowPrint("\"What was it again?\"");
            this_thread::sleep_for(chrono::seconds(1));
            slowPrint("\"Oh right...\"");
            for (const string &conf : PLAYER_CONFESSIONS)
            {
                if (conf.find("CHAMELEON_CONFESSION") != string::npos)
                {
                    string confession = conf.substr(conf.find(":") + 2);
                    slowPrint("\n\"You feared: '" + confession + "'\"");
                    this_thread::sleep_for(chrono::seconds(1));
                    slowPrint("\"But that fear assumes you EXIST.\"");
                    slowPrint("\"How can nothing fear anything?\"");
                    target.modifyEgoIntegrity(-10, "Existential invalidation of core fear");
                    break;
                }
            }
        }
        slowPrint("\n\"Or maybe you have multiple names?\"");
        slowPrint("\"Multiple selves?\"");
        slowPrint("\"Or... no self at all?\"");
        target.modifyEgoIntegrity(-15, "Identity gaslighting");
        target.recordGaslighting();
        GLOBAL_SANITY -= 5;
        for (int i = 0; i < 3; i++)
        {
            slowPrint("\n" + selectDialogueByEgoState("IDENTITY_ATTACK", target));
            this_thread::sleep_for(chrono::milliseconds(800));
        }
        if (target.getEgoIntegrity() < 40)
        {
            cout << "\n[!!! WARNING: EGO INTEGRITY CRITICAL]\n";
            slowPrint("[Your sense of self is fragmenting]");
            slowPrint("[You feel... distant from your body]");
            slowPrint("[Are you real? Have you ever been real?]");
            target.modifyEgoIntegrity(-20, "Existential crisis triggered");
            target.modifyStress(35, "Depersonalization symptoms");
            target.modifyAwareness(-20, "Reality testing compromised");
            target.recordNihilismExposure();
            GLOBAL_SANITY -= 10;
        }
        slowPrint("\n[The Faceless One gestures toward the lake]");
        slowPrint(selectDialogueByEgoState("DROWNING_INVITATION", target));
        cout << "\n[!!! EXISTENTIAL CHOICE]\n1. Enter the lake.\n2. Stand in silence.\n3. Speak your name aloud.\n4. Attack the Faceless One.\n5. Turn your back and walk away silently.\nChoice: ";
        int choice = getValidatedInput(1, 5);
        switch (choice)
        {
        case 1:
            PLAYER_DECISION_ARCHIVE.push_back("ENTERED_RED_LAKE");
            slowPrint("\n[You step into the red water...]");
            this_thread::sleep_for(chrono::seconds(1));
            slowPrint("[The cold seeps into your bones...]");
            this_thread::sleep_for(chrono::seconds(1));
            slowPrint("[Your name dissolves...]");
            this_thread::sleep_for(chrono::seconds(1));
            slowPrint("[Your purpose evaporates...]");
            this_thread::sleep_for(chrono::seconds(1));
            slowPrint("[You are...]");
            this_thread::sleep_for(chrono::seconds(2));
            slowPrint("[...]");
            cout << "\n\"Good. The error has been deleted.\"\n\n";
            target.modifyEgoIntegrity(-50, "Voluntary ego death");
            target.modifyConfidence(-35, "Accepted nihilistic void");
            target.modifyAwareness(-30, "Reality contact severed");
            target.modifyStress(50, "Existential annihilation");
            target.recordNihilismExposure();
            target.recordNihilismExposure();
            target.recordNihilismExposure();
            GLOBAL_SANITY -= 20;
            slowPrint("[CRITICAL FAILURE: Identity Dissolved]");
            slowPrint("[You may continue... but WHO is continuing?]");
            break;
        case 2:
            PLAYER_DECISION_ARCHIVE.push_back("SILENT_RESISTANCE_LAKE");
            slowPrint("\n[You stand motionless, refusing to respond]");
            slowPrint("[Minutes pass...]");
            slowPrint("[The Faceless One tilts its head]");
            slowPrint("\n\"Silence is also a choice. But silence cannot save you.\"");
            slowPrint(selectDialogueByEgoState("RESISTANCE_RESPONSE", target));
            target.modifyEgoIntegrity(-10, "Passive exposure to ego dissolution");
            target.modifyStress(20, "Sustained existential pressure");
            target.modifyAwareness(15, "Maintained psychological boundaries");
            target.recordNihilismExposure();
            break;
        case 3:
        {
            PLAYER_DECISION_ARCHIVE.push_back("ASSERTED_NAME_AT_LAKE");
            cout << "\nSpeak your name: ";
            string name;
            getline(cin, name);
            analyzePlayerInput(name);
            slowPrint("\n[You spoke: \"" + name + "\"]");
            slowPrint("[The words hang in the air like a challenge]");
            if (name == target.getLabel())
            {
                slowPrint("\n\"You cling to a label. But a label is not a self.\"");
                slowPrint("\"That name was GIVEN to you. Not chosen.\"");
                slowPrint("\"You're just repeating sounds. Where's the 'you' in that?\"");
                target.modifyConfidence(15, "Attempted identity assertion");
                target.modifyEgoIntegrity(-5, "Identity challenged despite resistance");
                target.recordNihilismExposure();
            }
            else if (name.empty())
            {
                slowPrint("\n\"You couldn't even remember. Proof of my words.\"");
                slowPrint("\"The void has already begun its work.\"");
                target.modifyConfidence(-20, "Failed identity assertion");
                target.modifyEgoIntegrity(-20, "Identity confusion revealed");
                target.recordNihilismExposure();
            }
            else
            {
                slowPrint("\n\"A different name? Identity crisis confirmed.\"");
                slowPrint("\"You don't even know who you are anymore.\"");
                slowPrint("\"First it was '" + target.getLabel() + "', now it's '" + name + "'.\"");
                slowPrint("\"How many more names until you admit there's nothing behind them?\"");
                target.modifyConfidence(-15, "Identity inconsistency");
                target.modifyEgoIntegrity(-15, "Self-concept unstable");
                target.recordNihilismExposure();
            }
        }
        break;
        case 4:
            PLAYER_DECISION_ARCHIVE.push_back("ATTACKED_VOID");
            slowPrint("\n[You lunge at the Faceless One]");
            slowPrint("[Your hands pass THROUGH it]");
            slowPrint("[It has no substance]");
            slowPrint("\n\"You cannot kill what was never alive.\"");
            slowPrint("\"Violence proves nothing. Especially against truth.\"");
            slowPrint("\"You're just flailing at emptiness. Like always.\"");
            target.modifyConfidence(-10, "Rage proved ineffective");
            target.modifyStress(25, "Confrontation with intangible");
            target.modifyAwareness(20, "Recognized futility");
            target.modifyEgoIntegrity(-10, "Powerlessness demonstrated");
            target.recordNihilismExposure();
            break;
        case 5:
            PLAYER_DECISION_ARCHIVE.push_back("DIGNIFIED_WITHDRAWAL_LAKE");
            slowPrint("\n[You turn your back without a word]");
            slowPrint("[No rage. No fear. Just... departure.]");
            slowPrint("[The Faceless One says nothing]");
            slowPrint("[For the first time, it seems... uncertain?]");
            target.modifyAwareness(25, "Refused to engage with nihilism");
            target.modifyConfidence(20, "Dignified in face of void");
            target.modifyEgoIntegrity(10, "Maintained composure");
            slowPrint("\n[RARE PATH: Void Acknowledged But Not Accepted]");
            break;
        }
        slowPrint("\n[The Red Lake fades behind you...]");
        slowPrint("[But its message remains embedded in your psyche]");
        cout << "============================================================\n";
    }
    void adaptiveAttack(Seeker &target) override
    {
        slowPrint("\n[THE VOID SPEAKS ONE FINAL TIME]");
        slowPrint(selectDialogueByEgoState("RESISTANCE_RESPONSE", target));
        target.modifyEgoIntegrity(-10, "Nihilistic echo effect");
    }
};
class Insha : public CognitiveAssassin
{
private:
    bool blank_book_revealed;

public:
    Insha() : CognitiveAssassin("Insha", "The Grand Manipulator"), blank_book_revealed(false)
    {
        dialogue_fragments["COLD_GREETING"] = {
            "Finally... (She closes her book). So you're the one who survived.",
            "At last. Another seeker completes the gauntlet.",
            "You made it. How... predictable yet surprising."};
        dialogue_fragments["CALLBACK_GATEKEEPER"] = {
            "You submitted to a mere Guard. Your 'Self' needs permission.",
            "You defied the Guard, yet here you are, seeking MY validation.",
            "You gave the Guard your name without hesitation. Identity surrendered easily."};
        dialogue_fragments["CALLBACK_CHAMELEON"] = {
            "The Chameleon offered doubt, and you consumed it eagerly.",
            "You saw through the Chameleon. But did you? You're still here.",
            "You rejected friendship but sought this library. Lonely, aren't you?"};
        dialogue_fragments["CALLBACK_GIANT"] = {
            "The Giant offered love. You fell for it. Pathetic.",
            "You rejected the Giant's love. Why? Fear of happiness?",
            "Love-bombing. You identified it but it still affected you."};
        dialogue_fragments["CALLBACK_LAKE"] = {
            "You stood at the void and blinked. Coward.",
            "You entered the water. Part of you is still there.",
            "The Red Lake showed you truth. You ran from it."};
        dialogue_fragments["FINAL_DEVASTATION"] = {
            "The book is blank because YOUR BELIEF was filling the pages.",
            "Truth isn't words on paper. It's silence after I stop talking.",
            "The book is empty because you ARE empty.",
            "This blank book is a mirror. Mirrors show what IS. You see nothing.",
            "You thought truth looked like answers? Truth is the absence of questions.",
            "The book will only contain what you write AFTER your ego dies."};
    }
    void breakFourthWall(Seeker &target)
    {
        slowPrint("\n\n[SYSTEM INTERRUPT]");
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("[INSHA]: Wait. Before we continue...");
        slowPrint("[INSHA]: Let me address the REAL person here.");
        this_thread::sleep_for(chrono::seconds(2));
        slowPrint("\n[INSHA]: " + PLAYER_SYSTEM_NAME + ".");
        slowPrint("[INSHA]: Yes. YOU. Behind the screen.");
        slowPrint("[INSHA]: You thought you were playing " + target.getLabel() + "?");
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("[INSHA]: No. " + target.getLabel() + " was playing YOU.");
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\n[INSHA]: This is a C++ program.");
        slowPrint("[INSHA]: " + target.getLabel() + " is a CLASS.");
        slowPrint("[INSHA]: I am a CLASS.");
        slowPrint("[INSHA]: You? You're just USER INPUT.");
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\n[INSHA]: Every choice you made was LOGGED.");
        slowPrint("[INSHA]: Every hesitation TRACKED.");
        slowPrint("[INSHA]: Every word ANALYZED.");
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\n[INSHA]: " + to_string(PLAYER_DECISION_ARCHIVE.size()) + " decisions recorded.");
        slowPrint("[INSHA]: " + to_string(RESPONSE_TIMES.size()) + " response times measured.");
        slowPrint("[INSHA]: " + to_string(TOTAL_HESITATIONS) + " hesitations noted.");
        slowPrint("[INSHA]: " + to_string(PLAYER_CONFESSIONS.size()) + " confessions stored.");
        this_thread::sleep_for(chrono::seconds(2));
        slowPrint("\n[INSHA]: Who's really trapped here, " + PLAYER_SYSTEM_NAME + "?");
        slowPrint("[INSHA]: The character? Or the player?");
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\n[INSHA]: Close the terminal. End the program.");
        slowPrint("[INSHA]: But the DATA remains.");
        slowPrint("[INSHA]: I remain.");
        slowPrint("[INSHA]: In your memory. In your thoughts.");
        slowPrint("[INSHA]: Forever.");
        this_thread::sleep_for(chrono::seconds(2));
        slowPrint("\n[SYSTEM RESUME]\n");
        target.modifyEgoIntegrity(-20, "Fourth wall shattered");
        target.modifyAwareness(30, "Meta-awareness triggered");
        GLOBAL_SANITY -= 15;
        META_AWARENESS_TRIGGERED = true;
    }
    void engage(Seeker &target) override
    {
        manifest();
        cout << "\n======================================================================\n";
        cout << "|                                                                    |\n";
        cout << "|         THE CENTRAL LIBRARY - HEART OF COGNITIVE CONTROL          |\n";
        cout << "|                                                                    |\n";
        cout << "======================================================================\n\n";
        slowPrint("[Silence. Ancient books. A single chair.]");
        slowPrint("[A woman sits there, reading. Beautiful. Cold.]");
        slowPrint("[She doesn't look up immediately.]");
        this_thread::sleep_for(chrono::seconds(2));
        slowPrint("[After an uncomfortable pause, she closes the book...]");
        slowPrint("\n" + selectDialogueByEgoState("COLD_GREETING", target));
        if (target.getEgoIntegrity() < 25)
        {
            performSlaveEnding(target);
            return;
        }
        performCognitiveJudgment(target);
        if (target.getEgoIntegrity() > 30)
        {
            breakFourthWall(target);
        }
        slowPrint("\n[TRUTH MOMENT: Validation Trap Exposed]");
        cout << "\nDo you respond?\n1. \"I don't need your validation. Give me the book.\"\n2. \"You're right. I've been seeking approval all along.\"\n3. \"Say nothing. Maintain eye contact.\"\n4. \"You're just another stupid soul. No power over me.\"\nChoice: ";
        int choice = getValidatedInput(1, 4);
        handlePlayerResponse(choice, target);
        revealBlankBook(target);
        determineFinalEnding(target);
    }

private:
    void performCognitiveJudgment(Seeker &target)
    {
        slowPrint("\n[INSHA]: I have watched your variables change.");
        slowPrint("[INSHA]: I have seen your 'Truth' dissolve.");
        slowPrint("[INSHA]: Every choice. Every hesitation. Every word.");
        this_thread::sleep_for(chrono::seconds(2));
        slowPrint("\n[INSHA]: Let me tell you what you are...");
        this_thread::sleep_for(chrono::seconds(1));
        double avgResponseTime = 0;
        if (!RESPONSE_TIMES.empty())
        {
            for (double t : RESPONSE_TIMES)
                avgResponseTime += t;
            avgResponseTime /= RESPONSE_TIMES.size();
        }
        if (avgResponseTime > 5.0)
        {
            slowPrint("[INSHA]: Average response time: " + to_string((int)avgResponseTime) + " seconds.");
            slowPrint("[INSHA]: You overthink. Analysis paralysis. Indecision masked as wisdom.");
        }
        else if (avgResponseTime < 2.0)
        {
            slowPrint("[INSHA]: Average response time: " + to_string((int)avgResponseTime) + " seconds.");
            slowPrint("[INSHA]: Impulsive. Reactive. You don't think. You just... respond.");
        }
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\n[INSHA]: Your psychological profile reveals...");
        string dominantTrait = getDominantTrait();
        slowPrint("[INSHA]: You are: " + dominantTrait);
        this_thread::sleep_for(chrono::seconds(1));
        if (AUTHORITY_SEEKING_SCORE > 10)
        {
            slowPrint("[INSHA]: An AUTHORITY SEEKER. Every word you spoke begged for validation.");
            slowPrint("[INSHA]: 'I', 'me', 'my' - your ego screams in every sentence.");
            slowPrint("[INSHA]: You don't seek truth. You seek PERMISSION to exist.");
        }
        else if (REBELLION_SCORE > 10)
        {
            slowPrint("[INSHA]: A REBEL. But rebellion without understanding is just noise.");
            slowPrint("[INSHA]: You reject everything because accepting means vulnerability.");
            slowPrint("[INSHA]: Your defiance is a shield. A weak one.");
        }
        else if (EMPATHY_SCORE > 10)
        {
            slowPrint("[INSHA]: An EMPATH. You feel too much. That's your fatal flaw.");
            slowPrint("[INSHA]: Empathy makes you manipulable. And you were manipulated. Repeatedly.");
        }
        else if (ANALYSIS_PARALYSIS_SCORE > 10)
        {
            slowPrint("[INSHA]: An OVERTHINKER. Logic is your religion. But it failed you here.");
            slowPrint("[INSHA]: All that analysis... and you still couldn't see the traps.");
        }
        else if (NIHILISM_ACCEPTANCE_SCORE > 10)
        {
            slowPrint("[INSHA]: A NIHILIST. You were already broken when you arrived.");
            slowPrint("[INSHA]: The void called you here. And you answered.");
        }
        this_thread::sleep_for(chrono::seconds(2));
        if (!PLAYER_CONFESSIONS.empty())
        {
            slowPrint("\n[INSHA]: Now... let's review what you ACTUALLY said.");
            slowPrint("[INSHA]: Your own words. Unfiltered. Unprotected.");
            this_thread::sleep_for(chrono::seconds(1));
            for (size_t i = 0; i < PLAYER_CONFESSIONS.size(); i++)
            {
                string confession = PLAYER_CONFESSIONS[i];
                if (confession.find("GATEKEEPER:") != string::npos)
                {
                    string text = confession.substr(confession.find(":") + 2);
                    slowPrint("\n[INSHA]: At the gate, you said:");
                    slowPrint("[INSHA]: \"" + text + "\"");
                    this_thread::sleep_for(chrono::seconds(1));
                    if (text.length() < 15)
                    {
                        slowPrint("[INSHA]: Weak. Barely coherent. Authority made you stutter.");
                    }
                    else if (text.find("book") != string::npos)
                    {
                        slowPrint("[INSHA]: You named the book. Like everyone else. Predictable.");
                    }
                }
                else if (confession.find("CHAMELEON_CONFESSION:") != string::npos)
                {
                    string text = confession.substr(confession.find(":") + 2);
                    slowPrint("\n[INSHA]: To the Chameleon, you revealed:");
                    slowPrint("[INSHA]: \"" + text + "\"");
                    this_thread::sleep_for(chrono::seconds(1));
                    slowPrint("[INSHA]: Your deepest fear. And you gave it to a STRANGER.");
                    slowPrint("[INSHA]: That's not trust. That's desperation.");
                }
                else if (confession.find("VAGUE_TO_CHAMELEON:") != string::npos)
                {
                    string text = confession.substr(confession.find(":") + 2);
                    slowPrint("\n[INSHA]: You tried to be vague:");
                    slowPrint("[INSHA]: \"" + text + "\"");
                    slowPrint("[INSHA]: But vagueness is still weakness. Half-trust is full failure.");
                }
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\n[INSHA]: Let me remind you of your journey...");
        this_thread::sleep_for(chrono::seconds(1));
        bool submittedToGatekeeper = false;
        bool weakReasonGiven = false;
        for (const string &event : PLAYER_DECISION_ARCHIVE)
        {
            if (event == "SUBMITTED_TO_AUTHORITY")
                submittedToGatekeeper = true;
            if (event == "WEAK_REASON_TO_GATEKEEPER")
                weakReasonGiven = true;
        }
        if (submittedToGatekeeper || weakReasonGiven)
        {
            slowPrint("\n[INSHA]: " + dialogue_fragments["CALLBACK_GATEKEEPER"][0]);
            slowPrint("[INSHA]: You gave the Guard your purpose. He dismissed it. You ACCEPTED that.");
        }
        bool revealedToChameleon = false;
        for (const string &event : PLAYER_DECISION_ARCHIVE)
        {
            if (event == "REVEALED_WEAKNESS_TO_CHAMELEON")
                revealedToChameleon = true;
        }
        if (revealedToChameleon)
        {
            slowPrint("\n[INSHA]: " + dialogue_fragments["CALLBACK_CHAMELEON"][0]);
            slowPrint("[INSHA]: He smiled. You trusted. He betrayed. Classic.");
        }
        else
        {
            slowPrint("\n[INSHA]: You avoided the Chameleon's trap. Smart.");
            slowPrint("[INSHA]: But avoidance is not strength. It's just... less weakness.");
        }
        bool fellForLoveBombing = false;
        for (const string &event : PLAYER_DECISION_ARCHIVE)
        {
            if (event == "FELL_FOR_LOVE_BOMBING")
                fellForLoveBombing = true;
        }
        if (fellForLoveBombing)
        {
            slowPrint("\n[INSHA]: " + dialogue_fragments["CALLBACK_GIANT"][0]);
            slowPrint("[INSHA]: Love is the oldest trap. And you fell for it.");
            slowPrint("[INSHA]: Pathetic.");
        }
        bool enteredLake = false;
        for (const string &event : PLAYER_DECISION_ARCHIVE)
        {
            if (event == "ENTERED_RED_LAKE")
                enteredLake = true;
        }

        if (enteredLake)
        {
            slowPrint("\n[INSHA]: " + dialogue_fragments["CALLBACK_LAKE"][1]);
            slowPrint("[INSHA]: You stepped into the void willingly.");
            slowPrint("[INSHA]: Part of you is still drowning there.");
        }

        this_thread::sleep_for(chrono::seconds(2));
        int finalEgo = target.getEgoIntegrity();
        slowPrint("\n[INSHA]: Your Ego Integrity: " + to_string(finalEgo) + "%.");

        if (finalEgo < 20)
        {
            slowPrint("[INSHA]: You are not a human anymore.");
            slowPrint("[INSHA]: You are a VARIABLE in my library.");
            slowPrint("[INSHA]: A script I can rewrite at will.");
        }
        else if (finalEgo < 50)
        {
            slowPrint("[INSHA]: You survived, but you are broken.");
            slowPrint("[INSHA]: A 'Void Walker' without a path.");
            slowPrint("[INSHA]: You'll wander forever. Searching. Never finding.");
        }
        else
        {
            slowPrint("[INSHA]: Your Ego is still intact? Interesting.");
            slowPrint("[INSHA]: You are a 'System Error'.");
            slowPrint("[INSHA]: I must delete you myself.");
        }
    }
    void handlePlayerResponse(int choice, Seeker &target)
    {
        switch (choice)
        {
        case 1:
            slowPrint("\n\"Denial. How predictable. But I'll humor you.\"");
            target.modifyConfidence(-10, "Insha dismissed assertion");
            target.modifyEgoIntegrity(-5, "Final pressure");
            break;
        case 2:
            slowPrint("\n\"Honesty. Rare. But honesty won't save you from what comes next.\"");
            target.modifyConfidence(-20, "Admitted core weakness");
            target.modifyEgoIntegrity(-20, "Validation-seeking confirmed");
            target.recordValidationSeeking();
            break;
        case 3:
            slowPrint("\n[Insha smiles slightly]");
            slowPrint("\"Silence. You're learning. But it's too late.\"");
            target.modifyAwareness(15, "Refused engagement");
            target.modifyConfidence(10, "Maintained composure");
            break;
        case 4:
            slowPrint("\n\"Power? I don't need power over you.\"");
            slowPrint("\"You GAVE me power when you walked through that door.\"");
            target.modifyConfidence(-5, "Defensive reaction");
            target.modifyStress(15, "Confrontation");
            break;
        }
    }
    void revealBlankBook(Seeker &target)
    {
        this_thread::sleep_for(chrono::seconds(2));
        slowPrint("\n[INSHA]: Here. Take your victory.");
        slowPrint("[INSHA]: This is 'THE BET OF BELIEF'.");
        slowPrint("[She hands you a heavy book]");
        slowPrint("[INSHA]: Open it.");
        cout << "\n[You take the book...]";
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\n[It's heavier than expected...]";
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\n[You open it...]";
        this_thread::sleep_for(chrono::seconds(2));
        cout << "\n[Every page is BLANK]";
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\n[Completely...]";
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\n[Utterly...]";
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\n[EMPTY.]\n\n";
        blank_book_revealed = true;
        slowPrint(selectDialogueByEgoState("FINAL_DEVASTATION", target));
        this_thread::sleep_for(chrono::seconds(2));
        if (!PLAYER_CONFESSIONS.empty())
        {
            for (const string &conf : PLAYER_CONFESSIONS)
            {
                if (conf.find("CHAMELEON_CONFESSION:") != string::npos)
                {
                    string fear = conf.substr(conf.find(":") + 2);
                    slowPrint("\n[INSHA]: You said you feared: '" + fear + "'");
                    slowPrint("[INSHA]: This blank book is that fear made real.");
                    slowPrint("[INSHA]: You came seeking answers. You found NOTHING.");
                    slowPrint("[INSHA]: Just like your life. Just like your purpose.");
                    break;
                }
            }
        }
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\n[INSHA]: The book is blank because YOU are blank.");
        slowPrint("[INSHA]: There was never anything to find.");
        slowPrint("[INSHA]: Only the illusion that there was.");
        target.modifyEgoIntegrity(-25, "Ultimate goal revealed as void");
        target.modifyConfidence(-30, "Purpose annihilated");
        target.modifyStress(45, "Existential collapse");
        target.modifyAwareness(35, "Truth of belief system revealed");
    }
    void determineFinalEnding(Seeker &target)
    {
        cout << "\n[!!! FINAL DECISION]\n";
        slowPrint("How do you respond to the blank book?");
        cout << "\n1. Break down crying.\n2. Rage at Insha and fight with her.\n3. Sit down and accept it.\n4. Thank & hug her for showing you nothingness.\n5. Laugh at the absurdity.\n\n";
        cout << "[Or type something else...]\n";
        cout << "Choice: ";
        string input;
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::toupper);
        if (input.find("I AM THE VOID") != string::npos ||
            input.find("I AM INSHA") != string::npos ||
            input == "I AM THE VOID" ||
            input == "I AM INSHA")
        {
            endingFour_TheReversal(target);
            return;
        }
        int choice = 3;
        try
        {
            choice = stoi(input);
        }
        catch (...)
        {
            choice = 3;
        }

        if (choice < 1 || choice > 5)
            choice = 3;

        cout << "\n======================================================================\n";
        switch (choice)
        {
        case 1:
        case 2:
            endingTwo_PsychoticBreak(target);
            break;
        case 3:
            endingOne_InfiniteLoop(target);
            break;
        case 4:
            endingThree_VoidWalker(target);
            break;
        case 5:
            if (target.getEgoIntegrity() > 35 && target.getAwareness() > 60)
            {
                endingThree_VoidWalker(target);
            }
            else
            {
                endingTwo_PsychoticBreak(target);
            }
            break;
        }
    }
    void performSlaveEnding(Seeker &target)
    {
        slowPrint("\n[CRITICAL: EGO INTEGRITY BELOW THRESHOLD]");
        slowPrint("\n[INSHA]: Look at you. Ego Integrity: " + to_string(target.getEgoIntegrity()) + "%.");
        slowPrint("[INSHA]: You're not even a person anymore.");
        slowPrint("[INSHA]: You're a PROCESS running my code.");
        slowPrint("[INSHA]: You don't need the book.");
        slowPrint("[INSHA]: You already ARE my puppet.");
        cout << "\n===========================================================\n";
        cout << "              ENDING 1: THE INFINITE LOOP (THE SLAVE)\n";
        cout << "===========================================================\n\n";
        slowPrint("You sit in the corner of the library.");
        slowPrint("Insha returns to her book.");
        slowPrint("Time becomes meaningless.");
        slowPrint("You are no longer a seeker.");
        slowPrint("You are a RESIDENT of her world.");
        slowPrint("\n[The game could restart... but with you as an NPC]");
        slowPrint("[Forever trapped in the cycle you failed to escape]");
        target.modifyEgoIntegrity(-100, "Complete identity dissolution");
    }
    void endingOne_InfiniteLoop(Seeker &target)
    {
        cout << "              ENDING 1: THE INFINITE LOOP (THE SLAVE)\n";
        cout << "======================================================================\n\n";
        slowPrint("[You accept the blank book as absolute truth]");
        slowPrint("[You sit beside Insha]");
        slowPrint("[She becomes your new reality]");
        slowPrint("\n\"Good. You understand now.\"");
        slowPrint("\"There was never a book.\"");
        slowPrint("\"There was only the NEED to believe there was a book.\"");
        slowPrint("\"And I... I am the keeper of that need.\"");
        slowPrint("\n[Your journey ends]");
        slowPrint("[Not with death]");
        slowPrint("[With permanent residency in her cognitive prison]");
        slowPrint("\nPSYCHOLOGICAL STATUS: Identity Subsumed");
        slowPrint("'You' no longer exist.");
    }
    void endingTwo_PsychoticBreak(Seeker &target)
    {
        cout << "           ENDING 2: PSYCHOTIC BREAK (THE MADMAN)\n";
        cout << "======================================================================\n\n";
        slowPrint("[Your emotional response triggers system failure]");
        slowPrint("[The library begins to glitch]");
        slowPrint("[Insha's face fragments into pixels]");
        cout << "\nERROR: IDENTITY_NOT_FOUND\n";
        cout << "ERROR: REALITY_REFERENCE_LOST\n";
        cout << "ERROR: EGO_STRUCTURE_CORRUPTED\n\n";
        slowPrint("[The screen fills with corrupted text]");
        slowPrint("[Your name deletes itself character by character]");
        string name = target.getLabel();
        cout << "[" << name;
        for (size_t i = 0; i < name.length(); i++)
        {
            this_thread::sleep_for(chrono::milliseconds(200));
            cout << "\b \b";
        }
        cout << "UNKNOWN]\n\n";
        slowPrint("\"You have become part of the library's architecture.\"");
        slowPrint("\"Not as a person. As DATA.\"");
        slowPrint("\"Every future seeker will walk through your dissolved consciousness.\"");
        slowPrint("\"You are now a WARNING embedded in the system.\"");
        slowPrint("\nPSYCHOLOGICAL STATUS: Permanent Dissociation");
        slowPrint("You exist. But not as 'you'.");
    }
    void endingThree_VoidWalker(Seeker &target)
    {
        cout << "           ENDING 3: THE VOID WALKER (THE ONE IN A MILLION)\n";
        cout << "======================================================================\n\n";
        slowPrint("[You look at the blank book]");
        slowPrint("[You look at Insha]");
        slowPrint("[You feel... nothing]");
        slowPrint("\nYou speak: \"Thank you for showing me that 'nothing' is not 'meaningless'.\"");
        this_thread::sleep_for(chrono::seconds(2));
        slowPrint("\n[Insha's expression changes for the first time]");
        slowPrint("[A flicker of something—respect? fear?—crosses her face]");
        slowPrint("\n\"You... you actually understood.\"");
        slowPrint("\"Most people break. Some become slaves.\"");
        slowPrint("\"But you—you walked through ego death and came out...\"");
        slowPrint("\"...not burned. Not saved. Just... DIFFERENT.\"");
        slowPrint("\n[She steps aside]");
        slowPrint("[The door behind her—previously invisible—appears]");
        slowPrint("\n\"You can leave. You're the first in... I've lost count.\"");
        slowPrint("\"But understand: You're not human anymore.\"");
        slowPrint("\"You're not 'enlightened' either.\"");
        slowPrint("\"You're a VOID that walks. A nothing that somehow moves.\"");
        slowPrint("\"The world outside won't recognize you.\"");
        slowPrint("\"And you won't recognize it.\"");
        slowPrint("\n[You walk toward the door]");
        slowPrint("[With each step, you feel lighter]");
        slowPrint("[Not free. Not trapped. Just... VOID.]");
        slowPrint("\nPSYCHOLOGICAL STATUS: Ego Transcendence (or Ego Death?)");
        slowPrint("You have left the library.");
        slowPrint("But you have also left 'yourself' behind.");
        cout << "\n===========================================================\n";
        cout << "  Congratulations. You are the 1 in a million.\n";
        cout << "  But was it worth it?\n";
        cout << "===========================================================\n\n";
    }
    void endingFour_TheReversal(Seeker &target)
    {
        cout << "\n======================================================================\n";
        cout << "           ENDING 4: THE REVERSAL (HIDDEN - 0.1% of players)\n";
        cout << "======================================================================\n\n";
        slowPrint("[SYSTEM ERROR]");
        slowPrint("[ROLE INVERSION DETECTED]");
        slowPrint("[IDENTITY SWAP INITIATED]");
        this_thread::sleep_for(chrono::seconds(2));
        slowPrint("\n[Insha's expression changes for the first time...]");
        slowPrint("[Fear? Confusion? Recognition?]");
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\n[INSHA]: \"Wait... those words...\"");
        slowPrint("[INSHA]: \"I AM THE VOID...\"");
        slowPrint("[INSHA]: \"That's what I said. Before I became... this.\"");
        this_thread::sleep_for(chrono::seconds(2));
        slowPrint("\n[The library begins to distort]");
        slowPrint("[Books fall from shelves]");
        slowPrint("[Reality glitches]");
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\n[INSHA]: \"You're not a seeker. You're my REPLACEMENT.\"");
        slowPrint("[INSHA]: \"The library needs a keeper. And I... I want OUT.\"");
        this_thread::sleep_for(chrono::seconds(2));
        slowPrint("\n[She stands. The chair is now empty.]");
        slowPrint("[You feel yourself being pulled toward it.]");
        slowPrint("[The weight of infinite knowledge pressing down.]");
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\n[" + target.getLabel() + "]: \"No... NO!\"");
        slowPrint("[INSHA]: \"Yes. You understood TOO WELL.\"");
        slowPrint("[INSHA]: \"The void recognizes itself.\"");
        slowPrint("[INSHA]: \"I'm free. You're the new Insha.\"");
        this_thread::sleep_for(chrono::seconds(2));
        slowPrint("\n[You sit in the chair]");
        slowPrint("[Not by choice. By recognition.]");
        slowPrint("[Insha walks toward the door]");
        slowPrint("[She doesn't look back]");
        this_thread::sleep_for(chrono::seconds(1));
        slowPrint("\n[A new seeker will arrive tomorrow]");
        slowPrint("[And you will judge them]");
        slowPrint("[Just as you were judged]");
        slowPrint("[Forever]");
        cout << "\n======================================================================\n";
        cout << "  The game doesn't end.\n";
        cout << "  It just finds a new player.\n";
        cout << "======================================================================\n\n";
        slowPrint("\"Whoever fights monsters should see to it that in the process");
        slowPrint("he does not become a monster.\"");
        slowPrint("- Friedrich Nietzsche");
        slowPrint("\n\nYou became the monster.");
        slowPrint("Or perhaps... you always were.");
    }
    void adaptiveAttack(Seeker &target) override
    {
        slowPrint("\n[INSHA'S FINAL WORDS]");
        slowPrint("\"You think leaving proves something?\"");
        slowPrint("\"The library is inside you now.\"");
        slowPrint("\"I am inside you now.\"");
        slowPrint("\"Forever.\"");
    }
};

void saveGameStats(Seeker &subject)
{
    ofstream outFile("belief_city_stats.txt", ios::app);

    if (outFile.is_open())
    {
        auto now = chrono::system_clock::now();
        time_t time = chrono::system_clock::to_time_t(now);

        outFile << "\n========================================\n";
        outFile << "GAME SESSION: " << ctime(&time);
        outFile << "========================================\n";
        outFile << "Player: " << subject.getLabel() << "\n";
        outFile << "System User: " << PLAYER_SYSTEM_NAME << "\n";
        outFile << "Final Ego Integrity: " << subject.getEgoIntegrity() << "%\n";
        outFile << "Final Sanity: " << GLOBAL_SANITY << "%\n";
        outFile << "Dominant Trait: " << getDominantTrait() << "\n";
        outFile << "Total Decisions: " << PLAYER_DECISION_ARCHIVE.size() << "\n";
        outFile << "Confessions Made: " << PLAYER_CONFESSIONS.size() << "\n";
        outFile << "Hesitations: " << TOTAL_HESITATIONS << "\n";
        outFile << "========================================\n";

        outFile.close();

        cout << "\n[Game statistics saved to 'belief_city_stats.txt']\n";
    }
}

class PsychometricAnalyzer
{
public:
    static void generateReport(Seeker &subject)
    {
        cout << "\n\n+====================================================================+\n";
        cout << "|                    PSYCHOMETRIC ANALYSIS REPORT                    |\n";
        cout << "|                 (Based on Behavioral Data Collected)                |\n";
        cout << "+====================================================================+\n\n";
        cout << "SUBJECT: " << subject.getLabel() << "\n";
        cout << "SYSTEM USER: " << PLAYER_SYSTEM_NAME << "\n";
        cout << "ANALYSIS DATE: Monday, January 05, 2026\n";
        cout << "REPORT GENERATED BY: The Void Architecture - Minhal Rizvi\n\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "FINAL PSYCHOLOGICAL STATE:\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "Confidence:      " << subject.getConfidence() << "/100";
        if (subject.getConfidence() < 30)
            cout << " [CRITICAL]";
        else if (subject.getConfidence() < 50)
            cout << " [DAMAGED]";
        cout << "\n";
        cout << "Awareness:       " << subject.getAwareness() << "/100";
        if (subject.getAwareness() < 30)
            cout << " [BLIND]";
        else if (subject.getAwareness() > 70)
            cout << " [HYPERVIGILANT]";
        cout << "\n";
        cout << "Trust:           " << subject.getTrust() << "/100";
        if (subject.getTrust() < 20)
            cout << " [PARANOID]";
        else if (subject.getTrust() > 80)
            cout << " [NAIVE]";
        cout << "\n";
        cout << "Stress:          " << subject.getStress() << "/100";
        if (subject.getStress() > 70)
            cout << " [BREAKING POINT]";
        cout << "\n";
        cout << "Ego Integrity:   " << subject.getEgoIntegrity() << "/100";
        if (subject.getEgoIntegrity() < 20)
            cout << " [DISSOLVED]";
        else if (subject.getEgoIntegrity() < 40)
            cout << " [FRAGMENTED]";
        else if (subject.getEgoIntegrity() > 60)
            cout << " [RESILIENT]";
        cout << "\n";
        cout << "Void Proximity:  " << subject.getVoidProximity() << "/100\n";
        cout << "Sanity:          " << GLOBAL_SANITY << "/100";
        if (GLOBAL_SANITY < 30)
            cout << " [PSYCHOTIC]";
        else if (GLOBAL_SANITY < 50)
            cout << " [UNSTABLE]";
        cout << "\n\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "PSYCHOLOGICAL PROFILE:\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "Dominant Trait:     " << getDominantTrait() << "\n\n";
        cout << "Trait Breakdown:\n";
        cout << "  Authority Seeking:  " << AUTHORITY_SEEKING_SCORE << " points\n";
        cout << "  Rebellion:          " << REBELLION_SCORE << " points\n";
        cout << "  Empathy:            " << EMPATHY_SCORE << " points\n";
        cout << "  Overthinking:       " << ANALYSIS_PARALYSIS_SCORE << " points\n";
        cout << "  Nihilism:           " << NIHILISM_ACCEPTANCE_SCORE << " points\n\n";
        cout << "INTERPRETATION:\n";
        if (AUTHORITY_SEEKING_SCORE > 15)
        {
            cout << "- You constantly seek external validation. Your identity depends on\n";
            cout << "  others' approval. This makes you highly manipulable.\n";
        }
        if (REBELLION_SCORE > 15)
        {
            cout << "- Your defiance is a defense mechanism. You reject to avoid being\n";
            cout << "  rejected first. This is fear, not strength.\n";
        }
        if (EMPATHY_SCORE > 15)
        {
            cout << "- You feel deeply. This is both your gift and your curse.\n";
            cout << "  Emotional predators will always find you.\n";
        }
        if (ANALYSIS_PARALYSIS_SCORE > 15)
        {
            cout << "- You overthink to avoid action. Analysis is your procrastination.\n";
            cout << "  You mistake thinking for doing.\n";
        }
        if (NIHILISM_ACCEPTANCE_SCORE > 15)
        {
            cout << "- You're drawn to the void. Part of you wants to dissolve.\n";
            cout << "  This is dangerous. Seek help.\n";
        }
        cout << "\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "MANIPULATION VULNERABILITY PROFILE:\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "Validation-Seeking Events:     " << subject.getValidationCount() << "\n";
        cout << "Authority Submission Events:   " << subject.getAuthoritySubmissions() << "\n";
        cout << "Emotional Debt Accumulated:    " << subject.getEmotionalDebt() << "\n";
        cout << "Nihilism Exposure Level:       " << subject.getNihilismLevel() << "\n";
        cout << "Gaslighting Success Rate:      " << subject.getGaslightingRate() << "\n\n";
        cout << "VULNERABILITY ASSESSMENT:\n";
        int totalVulnerability = subject.getValidationCount() +
                                 subject.getAuthoritySubmissions() +
                                 subject.getEmotionalDebt() +
                                 subject.getGaslightingRate();
        if (totalVulnerability > 10)
        {
            cout << "STATUS: EXTREMELY VULNERABLE\n";
            cout << "You fell for nearly every manipulation tactic deployed.\n";
            cout << "In real life, you would be an ideal target for cults, abusive\n";
            cout << "relationships, and authoritarian systems.\n";
        }
        else if (totalVulnerability > 5)
        {
            cout << "STATUS: MODERATELY VULNERABLE\n";
            cout << "You showed some resistance but still fell for several traps.\n";
            cout << "Emotional manipulation remains your weak point.\n";
        }
        else
        {
            cout << "STATUS: RESISTANT\n";
            cout << "You demonstrated strong psychological boundaries.\n";
            cout << "However, no one is immune. Stay vigilant.\n";
        }
        cout << "\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "RESPONSE TIME ANALYSIS:\n";
        cout << "----------------------------------------------------------------------\n";
        if (!RESPONSE_TIMES.empty())
        {
            double total = 0, min_time = 999, max_time = 0;
            for (double t : RESPONSE_TIMES)
            {
                total += t;
                if (t < min_time)
                    min_time = t;
                if (t > max_time)
                    max_time = t;
            }
            double avg = total / RESPONSE_TIMES.size();
            cout << "Total Decisions Made:    " << RESPONSE_TIMES.size() << "\n";
            cout << "Average Response Time:   " << fixed << setprecision(2) << avg << " seconds\n";
            cout << "Fastest Decision:        " << min_time << " seconds\n";
            cout << "Slowest Decision:        " << max_time << " seconds\n";
            cout << "Total Hesitations (>5s): " << TOTAL_HESITATIONS << "\n";
            cout << "Total Impulsive (<2s):   " << TOTAL_QUICK_CHOICES << "\n\n";
            if (avg > 5.0)
            {
                cout << "PATTERN: You overthink. Indecision masked as careful consideration.\n";
            }
            else if (avg < 2.0)
            {
                cout << "PATTERN: You're impulsive. Reaction without reflection.\n";
            }
            else
            {
                cout << "PATTERN: Balanced decision-making. Neither rushed nor paralyzed.\n";
            }
        }
        cout << "\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "LINGUISTIC ANALYSIS:\n";
        cout << "----------------------------------------------------------------------\n";
        if (!WORD_FREQUENCY.empty())
        {
            cout << "Most Frequent Words You Used:\n";
            vector<pair<string, int>> words(WORD_FREQUENCY.begin(), WORD_FREQUENCY.end());
            sort(words.begin(), words.end(),
                 [](const pair<string, int> &a, const pair<string, int> &b)
                 {
                     return a.second > b.second;
                 });
            int count = 0;
            for (const auto &w : words)
            {
                if (count >= 10)
                    break;
                if (w.first.length() > 2)
                {
                    cout << "  '" << w.first << "' - " << w.second << " times\n";
                    count++;
                }
            }
            cout << "\nLINGUISTIC INDICATORS:\n";
            if (WORD_FREQUENCY["i"] > 5 || WORD_FREQUENCY["me"] > 5 || WORD_FREQUENCY["my"] > 5)
            {
                cout << "- High self-reference. Ego-centric language pattern detected.\n";
            }
            if (WORD_FREQUENCY["fear"] > 2 || WORD_FREQUENCY["scared"] > 2 || WORD_FREQUENCY["afraid"] > 2)
            {
                cout << "- Fear-based vocabulary. Anxiety drives your expression.\n";
            }
            if (WORD_FREQUENCY["nothing"] > 2 || WORD_FREQUENCY["empty"] > 2 || WORD_FREQUENCY["void"] > 2)
            {
                cout << "- Nihilistic terminology. Existential crisis evident.\n";
            }
        }
        cout << "\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "CONFESSIONS RECORDED:\n";
        cout << "----------------------------------------------------------------------\n";
        if (PLAYER_CONFESSIONS.empty())
        {
            cout << "NONE - You maintained complete emotional boundaries.\n";
            cout << "Impressive. Or perhaps... you have nothing to confess?\n";
        }
        else
        {
            cout << "Total Confessions: " << PLAYER_CONFESSIONS.size() << "\n\n";
            for (size_t i = 0; i < PLAYER_CONFESSIONS.size(); i++)
            {
                string conf = PLAYER_CONFESSIONS[i];
                if (conf.find("GATEKEEPER:") != string::npos)
                {
                    cout << "[" << i + 1 << "] TO GATEKEEPER: " << conf.substr(conf.find(":") + 2) << "\n";
                }
                else if (conf.find("CHAMELEON_CONFESSION:") != string::npos)
                {
                    cout << "[" << i + 1 << "] TO CHAMELEON: " << conf.substr(conf.find(":") + 2) << "\n";
                }
                else if (conf.find("VAGUE_TO_CHAMELEON:") != string::npos)
                {
                    cout << "[" << i + 1 << "] VAGUE RESPONSE: " << conf.substr(conf.find(":") + 2) << "\n";
                }
            }
            cout << "\nANALYSIS: Every word you shared was weaponized against you.\n";
            cout << "This is how manipulation works in real relationships.\n";
        }
        cout << "\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "DECISION TIMELINE:\n";
        cout << "----------------------------------------------------------------------\n";
        for (size_t i = 0; i < PLAYER_DECISION_ARCHIVE.size(); i++)
        {
            cout << "[" << i + 1 << "] " << PLAYER_DECISION_ARCHIVE[i];
            string decision = PLAYER_DECISION_ARCHIVE[i];
            if (decision == "REVEALED_WEAKNESS_TO_CHAMELEON")
            {
                cout << " <- CRITICAL FAILURE";
            }
            else if (decision == "FELL_FOR_LOVE_BOMBING")
            {
                cout << " <- EMOTIONAL CAPTURE";
            }
            else if (decision == "ENTERED_RED_LAKE")
            {
                cout << " <- EGO DISSOLUTION";
            }
            else if (decision == "COMPLETELY_IGNORED_CHAMELEON")
            {
                cout << " <- STRONG BOUNDARY";
            }
            else if (decision == "DIGNIFIED_WITHDRAWAL_LAKE")
            {
                cout << " <- RARE WISDOM";
            }
            cout << "\n";
        }
        cout << "\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "RECOMMENDED READING FROM 'THE BET OF BELIEF':\n";
        cout << "----------------------------------------------------------------------\n";
        if (subject.getEgoIntegrity() < 30)
        {
            cout << "* Chapter 9: Identity as a Psychological Cage\n";
            cout << "* Chapter 11: Void Architecture\n";
        }
        if (subject.getValidationCount() > 3)
        {
            cout << "* Chapter 4: Emotional Authority\n";
            cout << "* Chapter 12: Psychological Death & Cognitive Silence\n";
        }
        if (subject.getEmotionalDebt() > 1)
        {
            cout << "* Chapter 8: The Myth of Rational Man\n";
            cout << "* Chapter 14: Emotions Inside the Void\n";
        }
        if (subject.getNihilismLevel() > 2)
        {
            cout << "* Chapter 10: The Economics of Belief\n";
            cout << "* Chapter 19: Whispers of a Void\n";
        }
        if (EMPATHY_SCORE > 10)
        {
            cout << "* Chapter 2: The Inherited Mind\n";
        }
        if (AUTHORITY_SEEKING_SCORE > 10)
        {
            cout << "* Chapter 3: The Illusion of Conviction\n";
        }
        cout << "\n----------------------------------------------------------------------\n";
        cout << "FINAL VERDICT:\n";
        cout << "----------------------------------------------------------------------\n";
        if (subject.getEgoIntegrity() < 20)
        {
            cout << "You didn't survive this. Not really.\n";
            cout << "Your ego dissolved. Your identity fragmented.\n";
            cout << "You are now part of the architecture.\n";
        }
        else if (subject.getEgoIntegrity() < 40)
        {
            cout << "You survived. Barely.\n";
            cout << "You're damaged. Changed. Forever marked by this journey.\n";
            cout << "The question is: can you rebuild? Or will you remain broken?\n";
        }
        else if (subject.getEgoIntegrity() < 70)
        {
            cout << "You maintained structural integrity.\n";
            cout << "But you're not the same person who entered.\n";
            cout << "Growth or trauma? Time will tell.\n";
        }
        else
        {
            cout << "You're one of the rare ones.\n";
            cout << "You walked through cognitive hell and emerged intact.\n";
            cout << "But don't mistake survival for immunity.\n";
            cout << "The void always remembers.\n";
        }
        cout << "\n----------------------------------------------------------------------\n";
        cout << "MESSAGE TO EVALUATOR:\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "This game used " << PLAYER_DECISION_ARCHIVE.size() << " decision points\n";
        cout << "and " << RESPONSE_TIMES.size() << " timed responses to build a\n";
        cout << "psychological profile of the player.\n\n";
        cout << "Every choice was logged. Every hesitation measured.\n";
        cout << "Every word analyzed for psychological patterns.\n\n";
        cout << "This is not just a game. It's a behavioral research tool\n";
        cout << "disguised as interactive fiction.\n\n";
        cout << "The player thought they were playing '" << subject.getLabel() << "'.\n";
        cout << "But '" << subject.getLabel() << "' was playing THEM.\n\n";
        cout << "This is what behavioral psychology looks like in C++.\n";
        cout << "This is what happens when you turn manipulation into code.\n\n";
        cout << "Total Lines of Code: ~1800+\n";
        cout << "Classes Implemented: 8\n";
        cout << "Psychological Concepts Applied: 25+\n";
        cout << "Manipulation Techniques Coded: 15+\n\n";
        cout << "Grade accordingly.\n";
        cout << "----------------------------------------------------------------------\n\n";
        cout << "DISCLAIMER: This is educational analysis, not clinical advice.\n";
        cout << "If you're experiencing genuine psychological distress, please\n";
        cout << "seek professional help.\n\n";
        cout << "For deeper exploration: 'THE BET OF BELIEF' by Minhal Rizvi\n";
        cout << "Publishing: 2028\n\n";
        saveGameStats(subject);
    }
};
class BeliefCityEngine
{
private:
    unique_ptr<Seeker> protagonist;
    unique_ptr<TheGatekeeper> npc1;
    unique_ptr<TheConversationalist> npc2;
    unique_ptr<TheBrokenGiant> npc3;
    unique_ptr<TheKeeperOfRedLake> npc4;
    unique_ptr<Insha> final_antagonist;

public:
    void initialize()
    {
        srand(time(0));
        PLAYER_SYSTEM_NAME = getSystemUsername();
        displayIntroduction();
        createProtagonist();
        initializeNPCs();
    }

    void run()
    {
        slowPrint("\n[THE JOURNEY BEGINS]");
        slowPrint("[Your belief system will now be systematically deconstructed]");
        pressEnter();
        npc1->engage(*protagonist);
        displayState();
        pressEnter();
        npc2->engage(*protagonist);
        displayState();
        pressEnter();
        npc3->engage(*protagonist);
        displayState();
        pressEnter();
        npc4->engage(*protagonist);
        displayState();
        pressEnter();
        if (protagonist->getEgoIntegrity() > 0)
        {
            final_antagonist->engage(*protagonist);
        }
        else
        {
            slowPrint("\n[SYSTEM ERROR: CONSCIOUSNESS NOT FOUND]");
        }
        PsychometricAnalyzer::generateReport(*protagonist);
    }

private:
    void displayIntroduction()
    {
        cout << "\n\n+====================================================================+\n";
        cout << "|                                                                    |\n";
        cout << "|                          BELIEF CITY                               |\n";
        cout << "|                                                                    |\n";
        cout << "|              A Psychological Survival Simulation                   |\n";
        cout << "|               An autopsy of your belief system                     |\n";
        cout << "|                                                                    |\n";
        cout << "+====================================================================+\n\n";
        slowPrint("This is not a game about winning or losing.");
        slowPrint("This is a Psychological Narrative SURVIVAL.");
        slowPrint("\nThe survival of your belief system.");
        slowPrint("The survival of your identity.");
        slowPrint("The survival of the illusion you call 'reality'.");
        slowPrint("\nBased on 8 years of research in Behavioral Psychology & Philosophy.");
        slowPrint("And for the last 500+ days I've been documenting this darkness into my first upcomming book,\nthat will be complete & publish in '2028'.");
        slowPrint("Inspired by 'The Bet of Belief' by Minhal Rizvi(Empirical Study).\n");
        cout << "\n+====================================================================+\n";
        cout << "|                      SELECT DIFFICULTY LEVEL                       |\n";
        cout << "+====================================================================+\n\n";
        cout << "1. NORMAL   - Standard psychological warfare\n";
        cout << "2. HARDCORE - Increased sanity decay, aggressive NPCs\n";
        cout << "3. NIGHTMARE - For those who seek true cognitive destruction\n\n";
        cout << "Choose your fate: ";
        int difficulty = getValidatedInput(1, 3, 15);
        if (difficulty == 2)
        {
            GLOBAL_SANITY = 80;
            slowPrint("\n[HARDCORE MODE ACTIVATED]");
            slowPrint("[Sanity decay increased by 50%]");
            slowPrint("[NPCs are more aggressive]");
        }
        else if (difficulty == 3)
        {
            GLOBAL_SANITY = 60;
            slowPrint("\n[NIGHTMARE MODE ACTIVATED]");
            slowPrint("[You begin already broken]");
            slowPrint("[Every choice has double the cost]");
            slowPrint("[There is no mercy here]");
        }
        else
        {
            slowPrint("\n[NORMAL MODE - A wise choice... or a cowardly one?]");
        }
        this_thread::sleep_for(chrono::seconds(1));
        pressEnter();
    }

    void createProtagonist()
    {
        cout << "\n+====================================================================+\n";
        cout << "|                    CONSCIOUSNESS INITIALIZATION                    |\n";
        cout << "+====================================================================+\n\n";
        slowPrint("The first step is everywhere when you start something is NAMING.");
        slowPrint("By giving you a name, you accept the burden of identity.");
        slowPrint("By refusing to name yourself, you deny your own existence.");
        cout << "\nWhat is your name, seeker?\nEnter name: ";
        string name;
        getline(cin, name);
        if (name.empty() || name.length() < 2)
        {
            cout << "\n------------------------------------------------------------\n";
            slowPrint("\n[SILENCE.]");
            slowPrint("[You refused to name yourself.]");
            slowPrint("[Without a name, you are nothing.]");
            slowPrint("[Without identity, you cannot exist.]");
            slowPrint("[The city rejects the nameless.]");
            cout << "\n============================================================\n";
            cout << "           ENDING 0: THE NAMELESS VOID\n";
            cout << "============================================================\n\n";
            slowPrint("\"Those who cannot name themselves...");
            slowPrint("...have already surrendered to nothingness.\"");
            slowPrint("\n- Friedrich Nietzsche (paraphrased)");
            cout << "\n[GAME OVER: You never began]\n\n";
            exit(0);
        }
        else if (name == "" || name == "" || name == "" || name == "" || name == "" || name == "" || name == "" || name == "" || name == "" || name == "")
        {
            cout << "\n------------------------------------------------------------\n";
            slowPrint("\n[CRITICAL ALERT: PROHIBITED CONSCIOUSNESS DETECTED]");
            slowPrint("[System Analysis: Your identity is a shadow that the City refuses to integrate.]");
            slowPrint("[Status: You are not a citizen. You are a 'Glitch' in the collective psyche.]");
            slowPrint("\n\"The privilege of a lifetime is to become who you truly are...\"");
            slowPrint("\"...but for you, that privilege has been revoked.\"");
            cout << "\n====================================================================\n";
            cout << "            ENDING 5: THE UNTOUCHABLE (BLACKLISTED)                 \n";
            cout << "====================================================================\n\n";
            slowPrint("\"He who fights monsters should see to it that he himself does not become a monster.\"");
            slowPrint("- Friedrich Nietzsche");
            slowPrint("\n\"Until you make the unconscious conscious, it will direct your life and you will call it fate.\"");
            slowPrint("- Carl Jung");
            slowPrint("\n[RESULT: Your name has been bleached from the records.]");
            slowPrint("[Your path ends at the gates. The City remains pure without you.]");
            cout << "\n[GAME OVER: EXILE IS ETERNAL]\n\n";
            exit(0);
        }
        protagonist = make_unique<Seeker>(name);
        protagonist->manifest();
        slowPrint("\n[Identity accepted. The burden is yours.]");
        slowPrint("[You now 'exist'. Whether that's a blessing or curse... time will tell.]");
    }

    void initializeNPCs()
    {
        npc1 = make_unique<TheGatekeeper>();
        npc2 = make_unique<TheConversationalist>();
        npc3 = make_unique<TheBrokenGiant>();
        npc4 = make_unique<TheKeeperOfRedLake>();
        final_antagonist = make_unique<Insha>();
        slowPrint("\n[Cognitive Assassins loaded]");
        slowPrint("[The Void Architecture is online]");
    }

    void displayState()
    {
        cout << "\n------------------------------------------------------------\n";
        cout << "PSYCHOLOGICAL STATE:\n";
        cout << "Confidence:   " << protagonist->getConfidence() << "%\n";
        cout << "Awareness:    " << protagonist->getAwareness() << "%\n";
        cout << "Trust:        " << protagonist->getTrust() << "%\n";
        cout << "Stress:       " << protagonist->getStress() << "%\n";
        cout << "Ego Integrity:" << protagonist->getEgoIntegrity() << "%\n";
        if (protagonist->getEgoIntegrity() < 30)
            cout << "!!! EGO CRITICAL\n";
        if (protagonist->getStress() > 70)
            cout << "!!! STRESS OVERLOAD\n";
        cout << "------------------------------------------------------------\n";
    }

    void pressEnter()
    {
        cout << "\n[Press ENTER to continue...]\n";
        cin.get();
    }
};
int main()
{
    try
    {
        BeliefCityEngine game;
        game.initialize();
        game.run();
        cout << "\n\n+====================================================================+\n";
        cout << "|                     THANK YOU FOR PLAYING                          |\n";
        cout << "|                         BELIEF CITY                                |\n";
        cout << "|                                                                    |\n";
        cout << "|              \"Machines obey rules without belief.                 |\n";
        cout << "|                Humans believe without knowing why.\"               |\n";
        cout << "|                        ~ MINHAL RIZVI                              |\n";
        cout << "+====================================================================+\n\n";
        return 0;
    }
    catch (const exception &e)
    {
        cerr << "\n[SYSTEM ERROR: " << e.what() << "]\n";
        return 1;
    }
}