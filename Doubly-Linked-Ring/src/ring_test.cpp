#include <catch2/catch_all.hpp>
#include "ring.hpp"
#include <iostream>
#include <utility>
#include <string>

TEST_CASE("CONSTRUCTORS", "[ring]"){

    GIVEN("CREATING CONSTRUCTORS"){

        Ring<int> ring1;
        Ring<double> ring2;

        THEN("CONTRUCTORS ARE EMPTY"){

            CHECK(ring1.isEmpty());
            CHECK(ring2.isEmpty());
            

            AND_THEN("CONSTRUCTROS HAVE NO ELEMENTS"){

                CHECK(ring1.getRingLength() == 0);
                CHECK(ring2.getRingLength() == 0);
            }
        }
    }
}

TEST_CASE("INSERT METHODS", "[ring]"){

    GIVEN("CREATING SINGLE RING"){

        Ring<int> ring;
        CHECK(ring.isEmpty());

        WHEN("INSERT A FEW ELEMENTS BY push METHOD"){

            ring.push(1);
            ring.push(2);
            ring.push(3);
            ring.push(4);
            ring.push(5);
            ring.push(6);
            ring.push(7);
            ring.push(8);
            ring.push(9);
            ring.push(10);

            THEN("CREATED RING IS NOT EMPTY"){
                CHECK_FALSE(ring.isEmpty());

                AND_THEN("CREATED RING HAS 10 ELEMENTS"){
                    CHECK(ring.getRingLength() == 10);

                    AND_THEN("ring HAS ALL OF THE INSERTED ELEMENTS"){

                        CHECK(ring.find(1));
                        CHECK(ring.find(2));
                        CHECK(ring.find(3));
                        CHECK(ring.find(4));
                        CHECK(ring.find(5));
                        CHECK(ring.find(6));
                        CHECK(ring.find(7));
                        CHECK(ring.find(8));
                        CHECK(ring.find(9));
                        CHECK(ring.find(10));
                    }
                }
            }

            AND_WHEN("PUSHING BEFORE THE GIVEN ELEMENT'S DATA"){
                
                //checking if the pushing has been successfull
                CHECK(ring.pushBefore(20, 8));
                //current ring
                //1 2 3 4 5 6 7 20 8 9 10 
                
                THEN("RING IS LONGER IN SIZE"){
                    CHECK(ring.getRingLength() == 11);

                    AND_THEN("ring HAS INSERTED ELEMENT BEFORE SPECIFIED ONE"){

                        CHECK(ring.find(20));
                        //checking the elements after, before inserted one
                        CHECK(ring.getDataBeforeElem(8) == 20);
                        CHECK(ring.getDataAfterElem(20) == 8);
                        //checking if the elements is between proper elements;
                        CHECK(ring.getDataBetweenElem(8, 7) == 20);

                        AND_WHEN("PUSHING ELEMENT AFTER SPECIFIED DATA"){

                            CHECK(ring.pushAfter(33, 5));

                            THEN("ring SHOULD BE LONGER OF ONE ELEMENTS"){
                                CHECK(ring.getRingLength() == 12);

                                AND_THEN("THE PUSHED ELEMENTS SHOULD'VE BEEN INSERTED PROPERLY"){
                                    CHECK(ring.find(33));
                                    CHECK(ring.getDataBeforeElem(6) == 33);
                                    CHECK(ring.getDataAfterElem(5) == 33);
                                    CHECK(ring.getDataBetweenElem(6, 5) == 33);
                                }
                            }

                            AND_WHEN("PUSHING DATA BETWEEN ELEMENTS"){

                                CHECK(ring.pushBetween(44, 3, 4));
                                //checking if the length has increased after pushing
                                CHECK(ring.getRingLength() == 13);

                                THEN("ELEMENT HAS BEED INSERTED"){
                                    CHECK(ring.find(44));

                                    AND_THEN("THE ELEMENT SHOULD BE EXACTLY IN THE SPECIFIED PLACE"){
                                    
                                        CHECK(ring.getDataBeforeElem(4) == 44);
                                        CHECK(ring.getDataAfterElem(3) == 44);
                                        CHECK(ring.getDataBetweenElem(4, 3) == 44);
                                     }
                                }

                                
                            }
                        }
                    }
                }
            }
        }
    }
    //CHECKING THE PUSHING
    AND_GIVEN("CREATING ANOTHER SHORTER RING"){

        Ring<int> ring;
        CHECK(ring.isEmpty());

        AND_GIVEN("PUSHING ELEMENTS TO THE RING"){

            ring.push(1);
            ring.push(2);

            CHECK(ring.getRingLength() == 2);

            WHEN("PUSHING BEFORE ELEMENT"){
                ring.pushBefore(5, 2);
                CHECK(ring.getRingLength() == 3);

                THEN("RING SHOULD HAVE THIS ELEMENT EXACTLY BEFORE"){

                    CHECK(ring.getDataBeforeElem(2) == 5);
                    CHECK(ring.getDataAfterElem(1) == 5);
                }
            }
        }
    }

    SECTION("CHECKING EXCEPTIONS OF INSERT/GET METHODS"){
        
        GIVEN("CREATING NEW RING WITH ANOTHER DATA TYPE"){

            Ring<float> newRing;
            Ring<float> emptyRing;
            CHECK(newRing.isEmpty());
            CHECK(emptyRing.isEmpty());

            AND_GIVEN("PUSHING TWO ELEMENTS"){

                newRing.push(1.1);
                newRing.push(2.2);

                WHEN("PUSHING BEFORE/AFTER/BETWEEN NON EXISITING ELEMENTS"){

                    CHECK_THROWS_AS(newRing.pushAfter(4.4, 3.3), std::overflow_error);
                    CHECK_THROWS_AS(newRing.pushBefore(5.5, 1.2), std::overflow_error);
                    CHECK_THROWS_AS(newRing.pushBetween(6.6, 2.2, 8.8), std::overflow_error);

                    //pushing to empty ring
                    CHECK_THROWS_AS(emptyRing.pushAfter(4.4, 3.3), std::overflow_error);
                    CHECK_THROWS_AS(emptyRing.pushBefore(4.4, 3.3), std::overflow_error);
                    CHECK_THROWS_AS(emptyRing.pushBetween(4.4, 3.3, 2.2), std::overflow_error);

                    AND_WHEN("GETTING DATA FROM THE NEWRING"){

                        CHECK_THROWS_AS(newRing.getDataBeforeElem(3.3), std::overflow_error);
                        CHECK_THROWS_AS(newRing.getDataAfterElem(3.3), std::overflow_error);
                        CHECK_THROWS_AS(newRing.getDataBetweenElem(3.3, 4.4), std::underflow_error);
                    }
                }
            }
            
        }
    }
}

TEST_CASE("COPY CONSTRUCTORS", "[ring]"){

    GIVEN("CREATING THE ONE INSTANCE OF THE RING"){

        Ring<int> ring;
        //checking if the newly created ring is empty
        CHECK(ring.isEmpty());

        AND_GIVEN("FILLING THE CREATED RING WITH ELEMENTS"){
            for(int i = 0; i < 10; i++){
                ring.push(i);
            }

            CHECK_FALSE(ring.isEmpty());
            CHECK(ring.getRingLength() == 10);
            CHECK(ring.find(1));

            WHEN("CREATING A COPY CONSTRUCTOR"){

                Ring<int> copyRing(ring);

                THEN("COPY CONSTRUCTOR SHOULD HAVE EXACLTY THE SAME NUMBER OF ELEMENTS AS ring"){

                    //checking the length
                    CHECK(copyRing.getRingLength() == 10);
                    //checking the equality of the rings
                    CHECK(copyRing == ring);

                    AND_THEN("copyRing HAS EXACTLY THE SAME ELEMENTS"){
                        Ring<int>::Iterator it = ring.begin();
                        Ring<int>::Iterator copyIt = copyRing.begin();

                        do{
                            CHECK((*it) == (*copyIt));
                            it++;
                            copyIt++;
                        }while(it != ring.begin() && copyIt != copyRing.begin());
                    }
                    
                }
            }

        }
    }
}


TEST_CASE("REMOVE METHODS", "[ring]"){

    GIVEN("CREATING A RING"){
        Ring<int> ring;
        //checking if the ring is empty for sure
        CHECK(ring.isEmpty());

        AND_GIVEN("FILLING THE RING WITH ELEMENTS"){

                for(int i = 0; i < 10; i++){
                    ring.push(i + 1);
                    ring.push(i + 2);
                }
                ring.push(10);
                //1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,10

                //checking if the elements has been inserted
                CHECK(ring.getRingLength() == 21);

                WHEN("REMOVE ELEMENTS BY DATA"){

                    //checking if the elements to be deleted are in the ring
                    CHECK(ring.countElem(2) == 2);
                    //removing all fo the instances of the elements with data = 2
                    ring.removeAll(2);

                    THEN("RING HAS TWO ELEMENTS LESS"){
                        CHECK(ring.getRingLength() == 19);

                        AND_THEN("ring DOES NOT HAVE THESE DELETED ELEMENTS"){
                            CHECK_FALSE(ring.find(2));
                            CHECK(ring.countElem(2) == 0);
                        }
                    }
                }
                AND_WHEN("DELETE SEPCIFEID OCCURENCE OF THE REPETED ELEMENTS BY DATA"){

                    //method removeByOccurence return true if the element
                    //with a given key and occurence has been found and has been deleted
                    CHECK(ring.removeByOccur(10, 2));

                    THEN("ring HAS ONE ELEMENT LESS"){
                        CHECK(ring.getRingLength() == 20);

                        AND_THEN("DELETED ELEMENT HAS BEEN DELTED"){

                            //previously in the ring were three 10
                            //at the moment it should be 2 x 10
                            CHECK(ring.countElem(10) == 2);
                        }
                    }
                }
                AND_WHEN("REMOVE THIRD OCCURENCE OF 10"){

                    //removing third and the first occurance of 10
                    CHECK(ring.removeByOccur(10, 3));
                    CHECK(ring.removeByOccur(10));

                    THEN("ring HAS TWO ELEMENTS LESS"){
                        CHECK(ring.getRingLength() == 19);

                        AND_THEN("ring HAS ONLY ONE ELEMENT WITH DATA OF 10"){
                            CHECK(ring.countElem(10) == 1);
                            CHECK(ring.find(10));
                        }
                    }
                }

                //clearRing method
                AND_WHEN("CLEAR ALL OF THE ELEMENTS"){
                    ring.clearRing();

                    THEN("ring IS EMPTY"){
                        CHECK(ring.isEmpty());
                    }
                }

            AND_WHEN("REMOVING ELEMENTS BEFORE SPECIFIED"){

                CHECK(ring.removeBefore(6));
                CHECK(ring.getRingLength() == 20);

                THEN("THERE IS ONLY ONE 5 IN THE RING"){

                    CHECK(ring.countElem(5) == 1);
                    CHECK(ring.getDataBeforeElem(5) == 4);
                    CHECK(ring.getDataAfterElem(5) == 6);
                }
            }
            AND_WHEN("REMOVING ELEMENTS BEFORE SPECIFIED"){

                CHECK(ring.removeAfter(11));
                CHECK(ring.getRingLength() == 20);

                THEN("THERE IS ONLY ONE 5 IN THE RING"){

                    //there was three elments with data = 10
                    CHECK(ring.countElem(10) == 2);
                    CHECK(ring.getDataBeforeElem(1) == 11);
                }
            }

        }
    }

    SECTION("CHECKING THE EXCEPTIONS OF REMOVE METHODS"){

        GIVEN("CREATING A RING"){
        Ring<int> ring;
        //checking if the ring is empty for sure
        CHECK(ring.isEmpty());

        //creating one empty ring for exceptions
        Ring<int> emptyRing;
        CHECK(emptyRing.isEmpty());

            AND_GIVEN("FILLING THE RING WITH ELEMENTS"){

                for(int i = 0; i < 10; i++){
                    ring.push(i + 1);
                }
                // 1,2,3,4,5,6,7,8,9,10
                CHECK(ring.getRingLength() == 10);

                WHEN("PASSING INVALID ARGUMENTS TO THE removeByOccur"){

                    //data does not exists
                    CHECK_THROWS_AS(ring.removeByOccur(11), std::underflow_error);
                    CHECK_THROWS_AS(ring.removeByOccur(1, -1), std::out_of_range);
                    CHECK_THROWS_AS(ring.removeByOccur(11, 0), std::out_of_range);
                    //removing from empty ring
                    CHECK_THROWS_AS(emptyRing.removeByOccur(11), std::underflow_error);


                    AND_WHEN("PASSING INVALID ARGUMENTS TO THE removeAll"){

                        CHECK_THROWS_AS(ring.removeAll(20), std::overflow_error);
                        CHECK_THROWS_AS(emptyRing.removeAll(2), std::underflow_error);
                    }

                }
            }
        }
    }
}


TEST_CASE("OPERATORS OVERLOADING", "[ring]"){

    GIVEN("CREATING TWO RING INSTANCES"){

        Ring<int> firstRing;
        Ring<int> secondRing;
        CHECK(firstRing.isEmpty());
        CHECK(secondRing.isEmpty());

        //operator==
        CHECK(firstRing == secondRing);

        AND_GIVEN("FILLING ON OF THEM WITH ELEMENTS"){

            firstRing.push(2);
            firstRing.push(4);
            firstRing.push(6);
            firstRing.push(8);

            CHECK(firstRing.getRingLength() == 4);

            WHEN("ASSIGN THE firstRing TO THE secondRing"){

                secondRing = firstRing;

                THEN("secondRing SHOULD HAVE THE SAME LENGTH"){
                    CHECK(secondRing.getRingLength() == 4);

                    AND_THEN("SHOULD HAVE THE SAME ELEMENTS"){
                        CHECK(secondRing == firstRing);
                        CHECK(secondRing.find(2));
                        CHECK(secondRing.find(4));
                        CHECK(secondRing.find(6));
                        CHECK(secondRing.find(8));
                    }
                }

                AND_WHEN("INSERT ONE ELEMENT TO THE secondRing"){
                    secondRing.push(12);
                    CHECK(secondRing.getRingLength() == 5);

                    THEN("THE secondRing SHOULDN'T BE EQUAL TO THE firstRing"){

                        //operator!=
                        CHECK(secondRing != firstRing);

                        //operator>
                        CHECK(secondRing > firstRing);

                        //operator>=
                        CHECK(secondRing >= firstRing);

                        AND_WHEN("PUSHING NEW ELEMENTS TO THE firstRing"){
                            firstRing.push(20);
                            firstRing.push(29);

                            CHECK(firstRing.getRingLength() == 6);

                            THEN("secondRing SHOULD BE SMALLER THAN firstRing"){
                                
                                //operator<
                                CHECK(secondRing < firstRing);

                                //operator<=
                                CHECK(secondRing <= firstRing);
                            }

                            AND_WHEN("PUSHING TWO ELEMENTS TO THE secondRing"){

                                secondRing.push(20);
                                secondRing.push(29);
                                CHECK(secondRing.getRingLength() == 7);

                                AND_WHEN("PUSHING ONE ELEMENT TO THE firstRing"){
                                    firstRing.push(30);

                                    THEN("TWO RINGS SHOULD HAVE THE SAME NUMBER OF ELEMENTS"){
                                        //checking the ring length
                                        CHECK(firstRing.getRingLength() == secondRing.getRingLength());
                                        //operator<=
                                        CHECK(firstRing <= secondRing);
                                        //operator>=
                                        CHECK(firstRing >= secondRing);
                                     }

                                     AND_WHEN("ADDING ONE RING TO ANOTHER"){

                                         //operator+
                                         secondRing + firstRing;

                                         THEN("secondRing SHOULD INCREASE WITH ELEMENTS OF firstRing"){
                                             CHECK(secondRing.getRingLength() == 14);
                                             CHECK(secondRing.countElem(2) == 2);
                                             CHECK(secondRing.countElem(4) == 2);
                                             CHECK(secondRing.countElem(6) == 2);
                                             CHECK(secondRing.countElem(8) == 2);
                                             CHECK(secondRing.countElem(20) == 2);
                                             CHECK(secondRing.countElem(29) == 2);
                                             CHECK(secondRing.find(30));

                                         }

                                         AND_WHEN("ADDING TO THE firstRing THE secondRing"){

                                             //operator+=
                                             secondRing += firstRing;

                                             THEN("secondRing SHOULD INCREMENT WITH THE ELEMENTS OF firstRing AS WITH operator+"){
                                                 CHECK(secondRing.getRingLength() == 21);
                                                 CHECK(secondRing.countElem(2) == 3);
                                                CHECK(secondRing.countElem(4) == 3);
                                                CHECK(secondRing.countElem(6) == 3);
                                                CHECK(secondRing.countElem(8) == 3);
                                                CHECK(secondRing.countElem(20) == 3);
                                                CHECK(secondRing.countElem(29) == 3);
                                                CHECK(secondRing.countElem(30) == 2);
                                             }
                                         }
                                     }

                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


TEST_CASE("CHECKING THE SUBRINGS METHODS", "[ring]"){

    GIVEN("CREATING TWO RINGS"){

        Ring<int> source;
        Ring<int> subRing;
        CHECK(source.isEmpty());
        CHECK(subRing.isEmpty());

        AND_GIVEN("FILLING THE source RING ELEMENTS"){

            for(int i = 0; i < 8; i++){
                source.push(i * 5);
            }
            //0,5,10,15,20,25,30,35

            //CHECKING THE source RING AFTER PUSHING
            CHECK(source.getRingLength() == 8);
            CHECK(source.find(0));
            CHECK(source.find(5));
            CHECK(source.find(10));
            CHECK(source.find(15));
            CHECK(source.find(20));
            CHECK(source.find(25));
            CHECK(source.find(30));
            CHECK(source.find(35));

            WHEN("ASSIGN THE SUBRING OF THE source TO subRing CLOCKWISE"){
                subRing = source.subRing(3, 4, true, true);
                //15,20,25,30
                
                THEN("subRing SHOULD HAVE 4 ELEMENTS"){
                    CHECK(subRing.getRingLength() == 4);

                    AND_THEN("THE INSERTED ELEMENTS SHOULD AS FOLLOW"){
                        CHECK(subRing.find(15));
                        CHECK(subRing.find(20));
                        CHECK(subRing.find(25));
                        CHECK(subRing.find(30));

                        CHECK(subRing.getDataAfterElem(15) == 20);
                        CHECK(subRing.getDataAfterElem(20) == 25);
                        CHECK(subRing.getDataAfterElem(25) == 30);
                        CHECK(subRing.getDataAfterElem(30) == 15);
                        CHECK(subRing.getDataBeforeElem(15) == 30);

                    }
                }

                AND_WHEN("CLEARING THE subRing FROM ITS ELEMENTS"){
                    subRing.clearRing();
                    CHECK(subRing.isEmpty());
                    CHECK_THROWS_AS(subRing.find(15), std::underflow_error);

                    AND_WHEN("ASSIGN THE SUBRING TO THE subRing COUNTERCLOCKWISE"){
                        subRing = source.subRing(4, 5, true, false);
                        //20,15,10,5,0

                        THEN("subRing SHOULD HAVE 5 ELEMENTS"){
                            CHECK(subRing.getRingLength() == 5);

                            AND_THEN("THE INSERTED ELEMENTS SHOULD AS FOLLOW"){
                                CHECK(subRing.find(20));
                                CHECK(subRing.find(15));
                                CHECK(subRing.find(10));
                                CHECK(subRing.find(5));
                                CHECK(subRing.find(0));

                                CHECK(subRing.getDataAfterElem(20) == 15);
                                CHECK(subRing.getDataAfterElem(15) == 10);
                                CHECK(subRing.getDataAfterElem(10) == 5);
                                CHECK(subRing.getDataAfterElem(5) == 0);
                                CHECK(subRing.getDataAfterElem(0) == 20);
                                CHECK(subRing.getDataBeforeElem(0) == 5);
                            }
                        }
                    }
                    WHEN("ASSIGN THE SUBRING TO THE subRing in a different way"){

                        subRing = source.subRing(4, 3, false, false);

                       THEN("subRing SHOULD HAVE 5 ELEMENTS"){

                            CHECK(subRing.getRingLength() == 3);

                            AND_THEN("THE INSERTED ELEMENTS SHOULD AS FOLLOW"){
                                CHECK(subRing.find(20));
                                CHECK(subRing.find(15));
                                CHECK(subRing.find(10));

                                CHECK(subRing.getDataAfterElem(20) == 15);
                                CHECK(subRing.getDataAfterElem(15) == 10);
                                CHECK(subRing.getDataAfterElem(10) == 20);
                                CHECK(subRing.getDataBeforeElem(20) ==  10);
                            }
                        }
                    }
                }
            }
        }
    }
}

TEST_CASE("SPLIT METHOD", "[ring]"){

    GIVEN("CREATING THE SOURCE RING AND THE STD::PAIR INSTANCE"){

        Ring<int> source;
        CHECK(source.isEmpty());

        std::pair< Ring<int>, Ring<int> > splittedRings;

        AND_GIVEN("FILLING THE source RING WITH ELEMENTS"){
            for(int i = 1; i < 9; i++){
                source.push(i * 10);
            }
            //10,20,30,40,50,60,70,80

            //checking if the elements has been inserted properly
            CHECK(source.getRingLength() == 8);
            CHECK(source.find(10));
            CHECK(source.find(20));
            CHECK(source.find(30));
            CHECK(source.find(40));
            CHECK(source.find(50));
            CHECK(source.find(60));
            CHECK(source.find(70));
            CHECK(source.find(80));

            WHEN("SPLITTED THE source RING BY THE SPLIT METHOD  "){

                splittedRings = split(source, 2, 10, true, 3, true, 4, true);

                //first  30 40 50 20
                //second  60 70 80 10

                THEN("TWO RINGS IN SPLITTEDRINGS SHOULD HAVE SOME ELEMENTS"){
                    CHECK_FALSE(splittedRings.first.isEmpty());
                    CHECK_FALSE(splittedRings.second.isEmpty());

                    CHECK(splittedRings.first.getRingLength() == 4);
                    CHECK(splittedRings.second.getRingLength() == 4);

                    AND_THEN("RINGS HAS SPECIFIC ELEMENTS"){

                            CHECK(splittedRings.first.find(30));
                            CHECK(splittedRings.first.find(40));
                            CHECK(splittedRings.first.find(50));
                            CHECK(splittedRings.first.find(20));

                            CHECK(splittedRings.second.find(60));
                            CHECK(splittedRings.second.find(70));
                            CHECK(splittedRings.second.find(80));
                            CHECK(splittedRings.second.find(10));

                            CHECK(splittedRings.first.getDataAfterElem(30) == 40);
                            CHECK(splittedRings.first.getDataAfterElem(40) == 50);
                            CHECK(splittedRings.first.getDataAfterElem(50) == 20);
                            CHECK(splittedRings.first.getDataAfterElem(20) ==  30);

                            CHECK(splittedRings.second.getDataAfterElem(60) == 70);
                            CHECK(splittedRings.second.getDataAfterElem(70) == 80);
                            CHECK(splittedRings.second.getDataAfterElem(80) == 10);
                            CHECK(splittedRings.second.getDataAfterElem(10) ==  60);
                    }
                }

                AND_WHEN("CLEARING THE SPLITTERRINGS"){

                    splittedRings.first.clearRing();
                    splittedRings.second.clearRing();

                    CHECK(splittedRings.first.isEmpty());
                    CHECK(splittedRings.second.isEmpty());

                    AND_WHEN("USING THE SPLIT METHOD WITH DIFFERENT PARAMETERS"){

                        splittedRings = split(source, 5, 15, false, 3, true, 2, false);

                        THEN("TWO RINGS IN SPLITTEDRINGS SHOULD HAVE SOME ELEMENTS"){
                            CHECK_FALSE(splittedRings.first.isEmpty());
                            CHECK_FALSE(splittedRings.second.isEmpty());

                            CHECK(splittedRings.first.getRingLength() == 6);
                            CHECK(splittedRings.second.getRingLength() == 4);

                                AND_THEN("RINGS HAS SPECIFIC ELEMENTS"){

                                        CHECK(splittedRings.first.find(40));
                                        CHECK(splittedRings.first.find(50));
                                        CHECK(splittedRings.first.find(60));
                                        CHECK(splittedRings.first.find(10));
                                        CHECK(splittedRings.first.find(20));
                                        CHECK(splittedRings.first.find(30));

                                        CHECK(splittedRings.second.find(70));
                                        CHECK(splittedRings.second.find(50));
                                        CHECK(splittedRings.second.find(40));
                                        CHECK(splittedRings.second.find(80));

                                        CHECK(splittedRings.first.getDataAfterElem(40) == 50);
                                        CHECK(splittedRings.first.getDataAfterElem(50) == 60);
                                        CHECK(splittedRings.first.getDataAfterElem(60) == 10);
                                        CHECK(splittedRings.first.getDataAfterElem(20) ==  30);
                                        CHECK(splittedRings.first.getDataBetweenElem(30, 10) ==  20);
                                        CHECK(splittedRings.first.getDataAfterElem(30) ==  40);

                                        CHECK(splittedRings.second.getDataAfterElem(70) == 50);
                                        CHECK(splittedRings.second.getDataAfterElem(50) == 40);
                                        CHECK(splittedRings.second.getDataAfterElem(40) == 80);
                                        CHECK(splittedRings.second.getDataAfterElem(80) ==  70);
                                }
                        }
                    }
                }
            }
        }
    }
    SECTION("EXCEPTIONS IN THE SPLIT METHOD"){

        GIVEN("CREATING THE SOURCE RING AND THE STD::PAIR INSTANCE"){

        Ring<int> source;
        CHECK(source.isEmpty());

        std::pair< Ring<int>, Ring<int> > splittedRings;

            AND_GIVEN("FILLING THE source RING WITH ELEMENTS"){
                for(int i = 1; i < 9; i++){
                    source.push(i * 5);
                }

                //checking if the elements has been inserted properly
                CHECK(source.getRingLength() == 8);
                CHECK(source.find(5));
                CHECK(source.find(10));
                CHECK(source.find(15));
                CHECK(source.find(20));
                CHECK(source.find(25));
                CHECK(source.find(30));
                CHECK(source.find(35));
                CHECK(source.find(40));

                WHEN("PASSING INVALID ARGUMENTS TO THE METHOD"){

                    CHECK_THROWS_AS( (splittedRings = split(source, -1, 15, false, 3, true, 2, false )), std::invalid_argument);
                    CHECK_THROWS_AS( (splittedRings = split(source, 4, 0, false, 3, true, 2, false )), std::invalid_argument);
                    CHECK_THROWS_AS( (splittedRings = split(source, 4, 15, false, -1, true, 2, false )), std::invalid_argument);
                    CHECK_THROWS_AS( (splittedRings = split(source, -4, 15, false, 3, true, -1, false )), std::invalid_argument);


                    
                }
            }

            WHEN("CREATING THE EMPTY RING AND ANOTHER STD::PAIR"){

                 Ring<double> ring;
                 CHECK(ring.isEmpty());

                 std::pair< Ring<double>, Ring<double> > newPair;

                    AND_WHEN("TRYNG TO USE METHOD SPLIT ON THIS EMPTY RING"){
                        
                        CHECK_THROWS_AS( (newPair = split(ring, 4, 15, true, 4, false, 5, false)), std::overflow_error);
                    }
            }
        }
    }
}