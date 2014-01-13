#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LOVES_NAME "You"

typedef enum word_kind_e {
    WORD_KIND_NOUN,
    WORD_KIND_SUBJECT_PRONOUN,
    WORD_KIND_OBJECT_PRONOUN,
    WORD_KIND_POSSESSIVE,
    WORD_KIND_PAST_POSSESSIVE,
    WORD_KIND_BEING,
    WORD_KIND_VERB,
    WORD_KIND_ADJECTIVE,
    WORD_KIND_ADVERB,
    NUM_WORD_KINDS
} word_kind;

static const char* s_love_nouns[] = {
    "love",
    "sweetheart",
    "passion",
    "little grumpling",
    "guinea pig",
    "sweetie pie"
};

static const char* s_love_verbs[] = {
    "love",
    "admire",
    "adore",
    "treasure",
    "cherish",
    "like"
};

static const char* s_love_adjectives[] = {
    "alluring",
    "delightful",
    "enchanting",
    "splendid",
    "sweet",
    "beautiful",
    "pretty",
    "cute"
};

static const char* s_love_adverbs[] = {
    "affectionately",
    "fondly",
    "dearly",
    "tenderly",
    "devotedly",
    "sweetly"
};

typedef enum person_perspective_e {
    PERSPECTIVE_FIRST_PERSON = 0,
    PERSPECTIVE_SECOND_PERSON,
    PERSPECTIVE_THIRD_PERSON,
    NUM_PERSON_PERSPECTIVES
} person_perspective;

// accessed by person_perspective
static const char* s_love_subject_pronouns[] = {
    "I",
    "you"
};

// accessed by person_perspective
static const char* s_love_object_pronouns[] = {
    "me",
    "you"
};

// accessed by person_perspective
static const char* s_love_possessives[] = {
    "my",
    "your"
};

// accessed by person_perspective
static const char* s_love_past_possessives[] = {
    "mine",
    "yours"
};

// accessed by person_perspective
static const char* s_love_beings[] = {
    "am",
    "are",
    "is"
};

typedef enum sentence_mode_e {
    SENTENCE_MODE_SUBJECT_VERB_OBJECT = 0,
    SENTENCE_MODE_SUBJECT_VERB_OBJECT_ADVERB,
    SENTENCE_MODE_SUBJECT_IS_VERBED,
    SENTENCE_MODE_OBJECT_IS_ADJECTIVE,
    SENTENCE_MODE_SUBJECT_IS_VERBED_ADVERBLY,
    SENTENCE_MODE_SUBJECT_IS_FIRST_PERSON_POSSESSED_NOUN,
    NUM_SENTENCE_MODES
} sentence_mode;

int get_rand_between(int a, int b) {
    int lowerBound, upperBound;
    
    if (a < b) {
        lowerBound = a;
        upperBound = b;
    }
    else if (a > b) {
        lowerBound = b;
        upperBound = a;
    }
    else {
        return a; // a == b, range is only one number
    }
    
    return lowerBound + (rand() % (1 + (upperBound - lowerBound)));
}

person_perspective random_first_or_second_person() {
    return (rand() & 0x01) ? PERSPECTIVE_FIRST_PERSON : PERSPECTIVE_SECOND_PERSON;
}

person_perspective opposite(person_perspective oppOf) {
    return (oppOf == PERSPECTIVE_FIRST_PERSON) ? PERSPECTIVE_SECOND_PERSON : PERSPECTIVE_FIRST_PERSON;
}

const char* get_subject_pronoun(person_perspective p) {
    return (p <= PERSPECTIVE_SECOND_PERSON) ? s_love_subject_pronouns[p] : s_love_subject_pronouns[PERSPECTIVE_SECOND_PERSON];
}

const char* get_object_pronoun(person_perspective p) {
    return (p <= PERSPECTIVE_SECOND_PERSON) ? s_love_object_pronouns[p] : s_love_object_pronouns[PERSPECTIVE_SECOND_PERSON];
}

const char* get_being(person_perspective p) {
    return (p <= PERSPECTIVE_THIRD_PERSON) ? s_love_beings[p] : s_love_beings[PERSPECTIVE_SECOND_PERSON];
}

const char* get_past_possessed(person_perspective p) {
    return (p <= PERSPECTIVE_SECOND_PERSON) ? s_love_past_possessives[p] : s_love_past_possessives[PERSPECTIVE_SECOND_PERSON];
}

const char* get_possessive(person_perspective p) {
    return (p <= PERSPECTIVE_SECOND_PERSON) ? s_love_possessives[p] : s_love_possessives[PERSPECTIVE_SECOND_PERSON];
}

const char* random_love_noun() {
    int numNouns = sizeof(s_love_nouns) / sizeof(const char*);
    int i = get_rand_between(0, numNouns - 1);
    
    if (i < 0 || i >= numNouns) {
        i = 0;
    }
    
    return s_love_nouns[i];
}

const char* random_love_verb() {
    int numVerbs = sizeof(s_love_verbs) / sizeof(const char*);
    int i = get_rand_between(0, numVerbs - 1);
    
    if (i < 0 || i >= numVerbs) {
        i = 0;
    }
    
    return s_love_verbs[i];
}

const char* random_love_adverb() {
    int numAdverbs = sizeof(s_love_adverbs) / sizeof(const char*);
    int i = get_rand_between(0, numAdverbs - 1);
    
    if (i < 0 || i >= numAdverbs) {
        i = 0;
    }
    
    return s_love_adverbs[i];
}

const char* random_love_adjective() {
    int numAdjectives = sizeof(s_love_adjectives) / sizeof(const char*);
    int i = get_rand_between(0, numAdjectives - 1);
    
    if (i < 0 || i >= numAdjectives) {
        i = 0;
    }
    
    return s_love_adjectives[i];
}

int snprint_svo_sentence(char* buffer, const int buflen) {
    const char* subject;
    const char* verb;
    const char* object;
    person_perspective subjectPerspective, objectPerspective;
    
    if (!buffer || buflen <= 0) {
        return 0;
    }
    
    subjectPerspective = PERSPECTIVE_FIRST_PERSON;
    objectPerspective = opposite(subjectPerspective);
    
    subject = get_subject_pronoun(subjectPerspective);
    object = get_object_pronoun(objectPerspective);
    verb = random_love_verb();
    
    return snprintf(buffer, buflen, "%s %s %s",
                    subject, verb, object);
}

int snprint_svoa_sentence(char* buffer, const int buflen) {
    const char* subject;
    const char* verb;
    const char* object;
    const char* adverb;
    person_perspective subjectPerspective, objectPerspective;
    
    if (!buffer || buflen <= 0) {
        return 0;
    }
    
    subjectPerspective = PERSPECTIVE_FIRST_PERSON;
    objectPerspective = opposite(subjectPerspective);
    
    subject = get_subject_pronoun(subjectPerspective);
    object = get_object_pronoun(objectPerspective);
    verb = random_love_verb();
    adverb = random_love_adverb();
    
    return snprintf(buffer, buflen, "%s %s %s %s",
                    subject, verb, object, adverb);
}

const char* get_past_verb_modifier(const char* verb) {
    int  len;
    char terminator;
    
    if (!verb) {
        return NULL;
    }
    
    len = strlen(verb);
    terminator = verb[len - 1];
    
    switch (terminator) {
    case 'e':
        return "d";
    default:
        return "ed";
    }
}

int snprint_s_is_v_sentence(char* buffer, const int buflen) {
    const char* subject;
    const char* isWord;
    const char* verb;
    const char* pastModifier;
//    const char* object;
    person_perspective subjectPerspective; // objectPerspective;
    
    if (!buffer || buflen <= 0) {
        return 0;
    }
    
    subjectPerspective = PERSPECTIVE_SECOND_PERSON;
//    objectPerspective = opposite(subjectPerspective);
    
    subject = get_subject_pronoun(subjectPerspective);
    isWord = get_being(subjectPerspective);
    verb = random_love_verb();
    pastModifier = get_past_verb_modifier(verb);
//    object = get_object_pronoun(objectPerspective);
    
    return snprintf(buffer, buflen, "%s %s %s%s",
                    subject, isWord, verb,
                    (pastModifier) ? pastModifier : "");
}

int snprint_o_is_a_sentence(char* buffer, const int buflen) {
    const char* object;
    const char* isWord;
    const char* adjective;
    person_perspective objectPerspective = PERSPECTIVE_SECOND_PERSON;
    
    if (!buffer || buflen <= 0) {
        return 0;
    }
    
    object = get_object_pronoun(objectPerspective);
    isWord = get_being(objectPerspective);
    adjective = random_love_adjective();
    
    return snprintf(buffer, buflen, "%s %s %s",
                    object, isWord, adjective);
}

int snprint_s_is_v_a(char* buffer, const int buflen) {
    const char* subject;
    const char* isWord;
    const char* verb;
    const char* pastModifier;
    const char* adverb;
    person_perspective subjectPerspective;//, possessorPerspective;
    
    if (!buffer || buflen <= 0) {
        return 0;
    }
    
    subjectPerspective = PERSPECTIVE_SECOND_PERSON;
    //possessorPerspective = opposite(subjectPerspective);
    
    subject = get_subject_pronoun(subjectPerspective);
    isWord = get_being(subjectPerspective);
    verb = random_love_verb();
    pastModifier = get_past_verb_modifier(verb);

    adverb = random_love_adverb();
    
    return snprintf(buffer, buflen, "%s %s %s%s, %s",
                    subject, isWord, verb,
                    (pastModifier) ? pastModifier : "",
                    adverb);
}

int snprint_s_is_fpp_n(char* buffer, const int buflen) {
    const char* subject;
    const char* isWord;
    const char* possessive;
    const char* noun;
    person_perspective subjectPerspective, possessorPerspective;
    
    if (!buffer || buflen <= 0) {
        return 0;
    }
    
    subjectPerspective = PERSPECTIVE_SECOND_PERSON;
    possessorPerspective = opposite(subjectPerspective);
    
    subject = get_subject_pronoun(subjectPerspective);
    isWord = get_being(subjectPerspective);
    possessive = get_possessive(possessorPerspective);
    noun = random_love_noun();
    
    return snprintf(buffer, buflen, "%s %s %s %s",
                    subject, isWord, possessive, noun);
}

sentence_mode random_sentence_mode() {
    return (sentence_mode)(get_rand_between(0, NUM_SENTENCE_MODES - 1));
}

int snprint_random_love_sentence(char* buffer, const int buflen) {
    sentence_mode mode;
    
    if (!buffer || buflen <= 0) {
        return 0;
    }
    
    mode = random_sentence_mode();
    
    switch (mode) {
    case SENTENCE_MODE_SUBJECT_VERB_OBJECT:
        return snprint_svo_sentence(buffer, buflen);
    case SENTENCE_MODE_SUBJECT_VERB_OBJECT_ADVERB:
        return snprint_svoa_sentence(buffer, buflen);
    case SENTENCE_MODE_SUBJECT_IS_VERBED:
        return snprint_s_is_v_sentence(buffer, buflen);
    case SENTENCE_MODE_OBJECT_IS_ADJECTIVE:
        return snprint_o_is_a_sentence(buffer, buflen);
    case SENTENCE_MODE_SUBJECT_IS_VERBED_ADVERBLY:
        return snprint_s_is_v_a(buffer, buflen);
    case SENTENCE_MODE_SUBJECT_IS_FIRST_PERSON_POSSESSED_NOUN:
        return snprint_s_is_fpp_n(buffer, buflen);
    default:
        return 0;
    }
}

void capitalize_first_letter(char* buffer, const int buflen) {
    int i;
    int len = buflen;
    
    if (!buffer || buflen <= 0) {
        return;
    }
    
    while (isspace(*buffer) && len > 0) {
        buffer++;
        len--;
    }
    
    if (len > 0) {
        *buffer = (char)(toupper(*buffer));
    }
}

int main(int argc, char** argv) {
    const int     buflen = 300;
    int           charsPrinted;
    char          strBuf[buflen];
    
    srand(time(NULL));
    
    charsPrinted = snprint_random_love_sentence(strBuf, buflen);
    
    capitalize_first_letter(strBuf, buflen);
    
    if (charsPrinted > 0) {
        printf("\nDear %s: %s.\n\n", LOVES_NAME, strBuf);    
    }
    
    return 0;
}


