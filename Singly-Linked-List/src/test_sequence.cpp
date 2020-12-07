#include <catch2/catch_all.hpp>
#include "sequence.hpp"
#include <iostream>


//basic constructor for the sequence for int data types
Sequence<int, int> seq1;

//creating one empty sequence for tests
Sequence<int, int> seq2;

TEST_CASE("CONSTRUCTORS", "[sequence]"){

    //checking constructors
    CHECK(seq1.isEmpty());
    CHECK(seq2.isEmpty());

}

TEST_CASE( "INSERT METHODS", "[sequence]" ) {


    //inserting elements by other methods
    seq1.insertAtBegining(1, 0);
    seq1.insertAtBegining(2, 7);
    seq1.insertAtBegining(3, 5);
    seq1.insertAtTheEnd(4, 5);
    seq1.insertAtTheEnd(5, 5);
    seq1.insertAfter(6, 6, 2, 1);


    //checking the sequence
    CHECK(seq1.sequenceLength() == 6);
    CHECK(seq1.findByInfo(7));
    CHECK(seq1.findByInfo(5, 3));
    CHECK(seq1.findByInfo(6));

    CHECK_FALSE(seq1.findByInfo(10));
    CHECK_FALSE(seq1.findByKey(15));
    

     SECTION("INSERT/FIND METHODS EXCEPTIONS"){

        CHECK_THROWS_AS(seq1.insertAfter(1,1,12), std::out_of_range);
        CHECK_THROWS_AS(seq1.insertAfter(1,1,4, 0), std::invalid_argument);

        //empty sequence
        CHECK_THROWS_AS(seq2.insertAfter(2,2,4), std::out_of_range);
        CHECK_THROWS_AS(seq2.findByInfo(5, 2), std::out_of_range);
        CHECK_THROWS_AS(seq2.findByInfo(5, -1), std::out_of_range);
    
    }
}

TEST_CASE("COPY CONSTRUCTOR", "[sequence]"){

    //classic copy cnstructor initialization
    Sequence<int, int> seq3(seq1);

    //checking false statement 
    CHECK_FALSE(seq3.isEmpty());
    
    //checking if the sequences are now equal to each other
    CHECK(seq3 == seq1);

    //checking the case for the empty sequence
    Sequence<int, int> seq4;
    CHECK(seq4.isEmpty());
    
    //copying the empty sequence in copy constructor
    Sequence<int, int> seq5(seq4);
    CHECK(seq5.isEmpty());
}

TEST_CASE("GET METHODS", "[sequence]"){

    SECTION("TESTING INSERTED ELEMENTS")
    //checking the info and key of each element of the seq1
    CHECK(seq1.getFirstElemInfo() == 5);
    CHECK(seq1.getLastElemInfo() == 5);
    CHECK(seq1.getInfoByKey(1) == 0);
    CHECK(seq1.getInfoByKey(2) == 7);
    CHECK(seq1.getInfoByKey(3) == 5);
    CHECK(seq1.getInfoByKey(4) == 5);
    CHECK(seq1.getInfoByKey(5) == 5);
    CHECK(seq1.getInfoByKey(6) == 6);
    CHECK(seq1.getInfoByKey(1) == 0);
    CHECK(seq1.getKeyByInfo(0) == 1);
    CHECK(seq1.getKeyByInfo(7) == 2);
    CHECK(seq1.getKeyByInfo(5) == 3);
    CHECK(seq1.getKeyByInfo(5,2) == 4);
    CHECK(seq1.getKeyByInfo(5, 3) == 5);
    CHECK(seq1.getKeyByInfo(6) == 6);



    SECTION("GET METHODS TESTING EXCEPTIONS"){

        //checking the exceptions of empty sequence
        
        CHECK_THROWS_AS(seq2.getInfoByKey(1, 1), std::out_of_range);
        CHECK_THROWS_AS(seq2.getFirstElemInfo(), std::out_of_range);
        CHECK_THROWS_AS(seq2.getLastElemInfo(), std::out_of_range);

        //checking the exceptions of filled sequence
        CHECK_THROWS_AS(seq1.getInfoByKey(1, 0), std::invalid_argument);
        CHECK_THROWS_AS(seq1.getInfoByKey(1, 0), std::invalid_argument);
        CHECK_THROWS_AS(seq1.getInfoByKey(1, 0), std::invalid_argument);
        CHECK_THROWS_AS(seq1.getInfoByKey(1, 0), std::invalid_argument);
        CHECK_THROWS_AS(seq1.getKeyByInfo(14), std::runtime_error);
    } 

}

TEST_CASE("OPERATORS", "[sequence]"){

    SECTION("LOGIC OPERATORS"){

    //operator ==
        //usage of the copy constructor to make two sequences the same
        Sequence<int, int> seq3(seq1);
        CHECK(seq3 == seq1);

        seq3.insertAtBegining(1,1);
        //checking equality after adding one element to seq3
        CHECK_FALSE(seq3 == seq1);

        //operator[]
        CHECK(seq3[0] == 1);

        //operator! =
        CHECK(seq3 != seq1);

        //operator >
        CHECK(seq3 > seq1); //seq3 has one more element than the seq1

        //operator <
        CHECK(seq1 < seq3);

        Sequence<int, int> seq4;
        //checking if the created sequence is empty
        CHECK(seq4.isEmpty());

        //inserting the same element in the seq4 as in the seq3
        seq4.insertAtBegining(1,1);

        //operator >=
        CHECK(seq3 >= seq4); //seq4 has only one element where seq has 6

        //operator <=
        CHECK(seq4 <= seq3);
    }

    SECTION("OVERLOADING OPERATORS"){
        
        //creating and checking wheter sequence is empty
        Sequence<int, int> seq4;
        CHECK(seq4.isEmpty());

        //operator =
        seq4 = seq1;
        CHECK(seq4.sequenceLength() == seq1.sequenceLength());
        CHECK(seq4 == seq1);

        //creating and checking wheter sequence is empty
        Sequence<int, int> seq6;
        CHECK(seq6.isEmpty());

        //operator +
        seq6 + seq1;
        CHECK(seq6.sequenceLength() == seq1.sequenceLength());

        //operator +=
        seq6 += seq1;
        CHECK(seq6.sequenceLength() == (seq1.sequenceLength() * 2));
    }
}

TEST_CASE("CLEARING THE SEQUENCE", "[sequence]"){

    Sequence<int, int> seq4;
    CHECK(seq4.isEmpty());

    seq4.insertAtTheEnd(1, 1);
    seq4.insertAtBegining(2,2);
    CHECK(seq4.sequenceLength() == 2);

    seq4.clearSequence();
    CHECK(seq4.isEmpty());

}

TEST_CASE("REMOVING METHODS", "[sequence]"){

    
    GIVEN("TWO ELEMENTS INSERTED INTO seq1"){
        
         //checking the sequence length after inserting
        seq1.insertAtBegining(12, 1);
        seq1.insertAtBegining(13, 2);
        CHECK(seq1.getFirstElemInfo() == 2);
        CHECK(seq1.sequenceLength() == 8);

        WHEN("REMOVE FIRST ELEMENT"){
            //removing the first element in the sequence
            CHECK(seq1.removeFirstElem());

            THEN("SEQUENCE IS SHORTER OF 1 ELEMENT"){
                CHECK(seq1.sequenceLength() == 7);
                CHECK(seq1.getFirstElemInfo() == 1);
                CHECK(seq1.getFirstElemKey() == 12);
            }

        }
     
    }

    AND_GIVEN("TWO ANOTHER ELEMENTS INSERTER AT THE BEGINNING"){

        seq1.insertAtTheEnd(14,3);
        seq1.insertAtTheEnd(15, 4);
        //checking the inserted elements
        CHECK(seq1.getLastElemInfo() == 4);
        CHECK(seq1.getLastElemKey() == 15);
        CHECK(seq1.sequenceLength() == 9);

        WHEN("REMOVED LAST ELEMENT"){
            //removing the last element
            CHECK(seq1.removeLastElem());

            THEN("ELEMENTS ARE DELETED"){

                //CHECKING THE LAST ELEMENTS
                CHECK(seq1.getLastElemInfo() == 3);
                CHECK(seq1.getLastElemKey() == 14);
                //checking whether such element exists
                CHECK(seq1.findByKey(14));

                AND_THEN("SEQUENCE IS SMALLER"){
                    CHECK(seq1.sequenceLength() == 8);

                    AND_WHEN("REMOVING BY GIVEN KEY"){
                        //checking the removing method
                        CHECK(seq1.removeByKey(14));
  
                        

                        THEN("PARTICULAR ELEMENT IS DELETED"){

                                //checkingif the element was removed properly
                                CHECK_FALSE(seq1.findByKey(14));
                                CHECK_FALSE(seq1.findByInfo(3));
                                CHECK_FALSE(seq1.findElem(14, 3));

                                AND_THEN("AND SEQUENCE IS SMALLER"){
                                    CHECK(seq1.sequenceLength() == 7);
                                }
                    } 
                }
                }     
            }
        }
    }
    AND_GIVEN("NEW ELEMENTS INSERTED"){

        //inserting elements which will be deleted
        seq1.insertAtBegining(15, 20);
        seq1.insertAtBegining(16, 20);
        //checking the sequence length after inserting the elements
        CHECK(seq1.sequenceLength() == 9);

        WHEN("REMOVING ELEMENTS BY GIVEN INFO"){
            //checking if the removing was successfull
            //removing two elements with info = 20
            CHECK(seq1.removeByInfo(20, 2));
            //removing one element with info = 5
            CHECK(seq1.removeByInfo(5));

            THEN("PARTICULAR ELEMENTS ARE DELETED"){
                //checking if the elements still exists
                CHECK_FALSE(seq1.findElem(15, 20));
                CHECK_FALSE(seq1.findElem(16, 20));
                CHECK_FALSE(seq1.findElem(3, 5));

                AND_THEN("SEQUENCE IS SMALLER"){
                    CHECK(seq1.sequenceLength() == 6);
                }
            }
        }
    }  
    AND_GIVEN("ONE ELEMENT INSERTED AT THE END OF THE SEQUENCE"){

        //inserting element which will be deleted
        seq1.insertAtTheEnd(18, 37);
        //and checking them
        CHECK(seq1.getLastElemInfo() == 37);
        CHECK(seq1.findElem(18, 37));

        WHEN("DELETE THIS ELEMENT BY removeAtPosition METHOD"){

            seq1.removeAtPosition(6);; //the last element

            THEN("DELETED ELEMENT DOES NOT EXISTS"){

                CHECK_FALSE(seq1.getLastElemInfo() == 37);
                CHECK_FALSE(seq1.findElem(18, 37));
            }
        }
    } 
}

TEST_CASE("SUBSEQUENCE METHODS", "[sequence]"){


        GIVEN("CREATING TWO SEQUENCES"){

            //creating the sequence instance where will be put the subsequence
            Sequence<int, int> subSeq;
            CHECK(subSeq.isEmpty());

            //creating the sequence from which will be retrived the subsequence
            Sequence<int, int> seqSource;
            CHECK(seqSource.isEmpty());

            AND_GIVEN("INSERTING ELEMENTS"){

                seqSource.insertAtTheEnd(0, 5);
                seqSource.insertAtTheEnd(1, 10);
                seqSource.insertAtTheEnd(2, 15);
                seqSource.insertAtTheEnd(3, 20);
                seqSource.insertAtTheEnd(4, 25);

                CHECK(seqSource.sequenceLength() == 5);

                WHEN("ASSIGNING THE RETURNED SUBSEQUENCE OF seqSource TO subSeq"){

                    subSeq = seqSource.subSeqFromBeginTo(2);

                    THEN("subSeq IS NOT EMPTY"){
                        CHECK_FALSE(subSeq.isEmpty());

                        AND_THEN("subSeq HAS EXACTLY THE SAME PART OF THE MANIPULATED SEQUENCE"){

                            CHECK(subSeq.getKeyByInfo(5) == 0);
                            CHECK(subSeq.getLastElemInfo() == 15);
                            CHECK(subSeq.getLastElemKey() == 2);
                            CHECK(subSeq.getKeyByInfo(10) == 1);
                            CHECK(subSeq.getKeyByInfo(15) == 2);

                            AND_THEN("subSeq HAS 3 ELEMENTS"){

                                CHECK(subSeq.sequenceLength() == 3);
                            }
                        }

                    }
                }
                AND_WHEN("ASSIGNING THE RETURNED SUBSEQUENCE FROM SOME ELEMENT TO THE END"){
                    
                    subSeq = seqSource.subSeqToEndFrom(2);

                    THEN("subSeq IS NOT EMPTY"){
                        CHECK_FALSE(subSeq.isEmpty());

                        AND_THEN("subSeq HAS EXACTLY THE SAME PART OF THE MANIPULATED SEQUENCE"){

                            CHECK(subSeq.getKeyByInfo(15) == 2);
                            CHECK(subSeq.getLastElemInfo() == 25);
                            CHECK(subSeq.getLastElemKey() == 4);
                            CHECK(subSeq.getFirstElemKey() == 2);
                            CHECK(subSeq.getFirstElemInfo() == 15);
                            CHECK(subSeq.getKeyByInfo(20) == 3);
                            CHECK(subSeq.getKeyByInfo(25) == 4);

                            AND_THEN("subSeq HAS 3 ELEMENTS"){

                                CHECK(subSeq.sequenceLength() == 3);
                            }
                        }

                    }

                }
                AND_WHEN("ASSIGNING THE RETURNED SUBSEQUENCE FROM SOME ELEMENT BY THE LENGTH"){
                    
                    subSeq = seqSource.subSeqFromByLength(1,3);

                    THEN("subSeq IS NOT EMPTY"){
                        CHECK_FALSE(subSeq.isEmpty());

                        AND_THEN("subSeq HAS EXACTLY THE SAME PART OF THE MANIPULATED SEQUENCE"){

                            CHECK(subSeq.getKeyByInfo(15) == 2);
                            CHECK(subSeq.getLastElemInfo() == 20);
                            CHECK(subSeq.getLastElemKey() == 3);
                            CHECK(subSeq.getFirstElemKey() == 1);
                            CHECK(subSeq.getFirstElemInfo() == 10);
                            CHECK(subSeq.getKeyByInfo(20) == 3);

                            AND_THEN("subSeq HAS 3 ELEMENTS"){

                                CHECK(subSeq.sequenceLength() == 3);
                            }
                        }

                    }

                }
            }
        } 
}

TEST_CASE("SHUFFLE METHOD", "[sequence]"){


    GIVEN("CREATING THREE EMPTY SEQUENCES"){

        Sequence<int, int> source1;
        CHECK(source1.isEmpty());

        Sequence<int, int> source2;
        CHECK(source2.isEmpty());

        Sequence<int, int> shuffleSeq;
        CHECK(shuffleSeq.isEmpty());

        AND_GIVEN("FILLING SEQUENCES source1, source2"){

            for(int i = 0; i <= 6; i++){
                source1.insertAtTheEnd(i, i * 2);
                source2.insertAtTheEnd(i + 6, (i + 2) * 10);
            };

            source1.printSequenceInfo();
            source2.printSequenceInfo();

            CHECK(source1.sequenceLength() == 7);
            CHECK(source1.sequenceLength() == source2.sequenceLength());

            WHEN("INVOKING THE SHUFLE METHOD WITH PASSING THESE TWO source1, source2 sequences"){

                shuffleSeq = shuffle(source1, 1, 2, source2, 1, 3, 15);

                THEN("shuffleSeq HAS ALL THE ELEMENTS"){
                    
                    //checking if the created sequence by the shuffle method
                    //has all of the elements of passed sequeneces
                    for(int i = 0; i <= 6; i++){
                        CHECK(source1.findElem(i, i * 2));
                        CHECK(source2.findElem(i + 6, (i + 2) * 10));
                    };

                    AND_THEN("THESE ELEMENTS ARE SORTED IN SOME WAY, SPECIFIED BY TH SHUFFLE ORIGIN"){
                        
                        //checking if all the elements has been "shuffled properly"
                        CHECK(shuffleSeq.getFirstElemInfo() == 2);
                        CHECK(shuffleSeq.getFirstElemKey() == 1);
                        CHECK(shuffleSeq.getLastElemInfo() == 12);
                        CHECK(shuffleSeq.getLastElemKey() == 6);


                        shuffleSeq.printSequenceInfo();

                        //checking all of the elements inside the "shuffled" sequence
                        CHECK(shuffleSeq[0] == 2);
                        CHECK(shuffleSeq[1] == 4);
                        CHECK(shuffleSeq[2] == 30);
                        CHECK(shuffleSeq[3] == 40);
                        CHECK(shuffleSeq[4] == 50);
                        CHECK(shuffleSeq[5] == 6);
                        CHECK(shuffleSeq[6] == 8);
                        CHECK(shuffleSeq[7] == 60);
                        CHECK(shuffleSeq[8] == 70);
                        CHECK(shuffleSeq[9] == 80);
                        CHECK(shuffleSeq[10] == 10);
                        CHECK(shuffleSeq[11] == 12);
                }
            }
             
        }
        AND_WHEN("shuffled SEQUENCE OF THE LIMIT SHORTER THAN THE SUM OF source1 + source2"){
                
                CHECK(shuffleSeq.isEmpty());

                //different indexes and lengths than previously
                shuffleSeq = shuffle(source1, 0, 3, source2, 2, 3, 8);

                shuffleSeq.printSequenceInfo();

                THEN("shuffleSeq HAS LENGTH EQUALS TO 8"){
                    CHECK(shuffleSeq.sequenceLength() == 8);
                    
                    AND_THEN("shuffleSeq HAS ELEMENTS IS PARTICULAR PATTERN"){

                        CHECK(shuffleSeq[0] == 0);
                        CHECK(shuffleSeq[1] == 2);
                        CHECK(shuffleSeq[2] == 4);
                        CHECK(shuffleSeq[3] == 40);
                        CHECK(shuffleSeq[4] == 50);
                        CHECK(shuffleSeq[5] == 60);
                        CHECK(shuffleSeq[6] == 6);
                        CHECK(shuffleSeq[7] == 8);
                    }
                
                }

            }
    }
    }
}
