#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

#include <set>
#include <string>
#include <vector>


TEST(LadderTest, CatToDog) {
  set<string> word_list;
  load_words(word_list, "src/words.txt");
  vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
  EXPECT_EQ(ladder.size(), 4);
}

TEST(LadderTest, MartyToCurls) {
  set<string> word_list;
  load_words(word_list, "src/words.txt");
  vector<string> ladder = generate_word_ladder("marty", "curls", word_list);
  EXPECT_EQ(ladder.size(), 6);
}

TEST(LadderTest, CodeToData) {
  set<string> word_list;
  load_words(word_list, "src/words.txt");
  vector<string> ladder = generate_word_ladder("code", "data", word_list);
  EXPECT_EQ(ladder.size(), 6);
}

TEST(LadderTest, WorkToPlay) {
  set<string> word_list;
  load_words(word_list, "src/words.txt");
  vector<string> ladder = generate_word_ladder("work", "play", word_list);
  EXPECT_EQ(ladder.size(), 6);
}

TEST(LadderTest, SleepToAwake) {
  set<string> word_list;
  load_words(word_list, "src/words.txt");
  vector<string> ladder = generate_word_ladder("sleep", "awake", word_list);
  EXPECT_EQ(ladder.size(), 8);
}

TEST(LadderTest, CarToCheat) {
  set<string> word_list;
  load_words(word_list, "src/words.txt");
  vector<string> ladder = generate_word_ladder("car", "cheat", word_list);
  EXPECT_EQ(ladder.size(), 4);
}