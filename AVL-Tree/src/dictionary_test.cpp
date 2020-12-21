#include <catch2/catch_all.hpp>
#include "dictionary.hpp"
#include <utility>



TEST_CASE("CONSTRUCTOR", "[dictionary]"){

    GIVEN("CREATING THE INSTANCE OF THE DICTIONARY CLASS"){

        Dictionary<std::string, int> source;

        THEN("THE dict1 SHOULD BE EMPTY"){
            CHECK(source.isEmpty());
            CHECK(source.getHeight() == 0);
            CHECK(source.getNumOfElem() == 0);
        }
    }
}


TEST_CASE("COPY CONSTRUCTOR", "[dictionary]"){

    GIVEN("CREATING THE INSTANCE OF THE DICTIONARY"){
        Dictionary<std::string, int> source;
        CHECK(source.isEmpty());

        AND_GIVEN("INSERTING SOME WORDS INTO THE TREE"){

            source.insert("New York", 4);
            source.insert("Warsaw", 5);
            source.insert("Chicago", 3);
            source.insert("Paris", 2);

            CHECK(source.getNumOfElem() == 4);

            THEN("TREE IS BALANCED"){
                CHECK(source.isTreeBalanced());

                AND_THEN("THE DICTIONARY HAS ALL OF THE INSERTED ELEMENTS"){
                    CHECK(source.findByKey("New York"));
                    CHECK(source.findByKey("Warsaw"));
                    CHECK(source.findByKey("Chicago"));
                    CHECK(source.findByKey("Paris"));

                    AND_WHEN("CREATING ANOTHER INSTANCE OF THE DICTIONARY BY COPYCONSTRUCTOR"){
                        Dictionary<std::string, int> copySource(source);

                        CHECK_FALSE( (copySource != source) );

                        THEN("THE copySource IS NOT EMPTY"){
                            CHECK_FALSE(copySource.isEmpty());

                            AND_THEN("THERE SHOULD BE 4 ELEMENTS IN THE DICTIONARY"){
                                CHECK(copySource.getNumOfElem() == 4);

                                AND_THEN("copySource HAS ALL COPIED ELEMENTS OF THE source"){
                                    CHECK(source.findByKey("New York"));
                                    CHECK(source.findByKey("Warsaw"));
                                    CHECK(source.findByKey("Chicago"));
                                    CHECK(source.findByKey("Paris"));
                                }
                            }
                        }
                    }
                }
            }

            
        }
    }
}

TEST_CASE("INSERTING THE ELEMENT INTO THE DICTIONARY", "[dictionary]"){
    
    GIVEN("CREATING ANOTHER INSTANCE OF THE DICTIONARY"){

        Dictionary<std::string, int> source;
        CHECK(source.isEmpty());
        CHECK(source.getHeight() == 0);

        WHEN("INSERTING THE ELEMENT INTO THE TREE"){
            source.insert("Apple", 3);
            CHECK(source.getNumOfElem() == 1);
    
            THEN("THE source SHOULD NOT BE EMPTY"){
                CHECK_FALSE(source.isEmpty());

                AND_THEN("THE HEIGHT OF THE AVL TREE SHOULD EQUAL TO 0"){
                    CHECK(source.getHeight() == 1);

                    AND_THEN("THE INSERTED ELEMENT SHOULD BE IN THE TREE"){
                        CHECK(source.findByKey("Apple"));

                        AND_THEN("THE NUMBER OF ELEMENTS IN THE TREE SHOULD BE 1"){
                            CHECK(source.getNumOfElem() == 1);
                        }

                        AND_THEN("TREE SHOULD BE BALANCED"){
                            CHECK(source.isTreeBalanced());
                        }
                    }
                }
            }
        }
        WHEN("INSERTING SOME A BUNCH OF NUMBERS OF ELEMENTS"){

            source.insert("Banana", 4);
            source.insert("Dragonfruit", 9);
            source.insert("Something", 11);
            source.insert("Car", 13);
            source.insert("Russia", 10);

            CHECK(source.getNumOfElem() == 5);

            THEN("THE source SHOULD NOT BE EMPTY"){
                CHECK_FALSE(source.isEmpty());
                
                AND_THEN("DICTIONARY HAS ALL OF THE INSERTED ELEMENTS"){
                    CHECK(source.findByKey("Banana"));
                    CHECK(source.findByKey("Dragonfruit"));
                    CHECK(source.findByKey("Something"));
                    CHECK(source.findByKey("Car"));
                    CHECK(source.findByKey("Russia"));
                    CHECK(source.count(4) == 1);
                    CHECK(source.count(9) == 1);
                    CHECK(source.count(11) == 1);
                    CHECK(source.count(13) == 1);
                    CHECK(source.count(10) == 1);

                    AND_THEN("THE TREE SHOULD BE BALANCED"){
                        CHECK(source.isTreeBalanced());

                    }

                    
                }
            }
        }
    }
}

TEST_CASE("REMOVING ELEMENTS", "[dictionary]"){
    
    GIVEN("CREATING THE INSTANCE OF DICTIONARY"){

        Dictionary<std::string, int> source;
        
        CHECK(source.isEmpty());
        
        AND_GIVEN("INSERTING SOME ELEMENTS"){

            source.insert("One", 7);
            source.insert("Two", 3);
            source.insert("Three", 5);   
            source.insert("Four", 12);
            source.insert("Five", 33);
            source.insert("Six", 9);  

            CHECK(source.getNumOfElem() == 6);

            CHECK_FALSE(source.isEmpty());

            THEN("THE TREE IS BALANCED"){
                CHECK(source.isTreeBalanced());
                
                AND_THEN("DICTIONARY HAS ALL OF THE ELEMENTS"){
                    CHECK(source.findByKey("One"));
                    CHECK(source.findByKey("Two"));
                    CHECK(source.findByKey("Three"));
                    CHECK(source.findByKey("Four"));
                    CHECK(source.findByKey("Five"));
                    CHECK(source.findByKey("Six"));

                     AND_WHEN("REMOVING LEAF ELEMENT - TWO"){
                        //source.display();
                        source.erase("Three");
                         CHECK(source.getNumOfElem() == 5); 

                        THEN("THE ERASED ELEMENT DOES NOT EXISTS"){
                            CHECK_FALSE(source.findByKey("Three"));
                            //tree is still balanced
                            CHECK(source.isTreeBalanced());
                        }
                        //source.display();

                        AND_WHEN("REMOVING THE ROOT ELEMENT"){
                        source.erase("One");
                        //source.display();
                        CHECK(source.getNumOfElem() == 4);

                            THEN("THE DICTIONARY DOES NOT HAVE THAT ELEMENT"){
                                CHECK(source.count(7) == 0);
                                CHECK_FALSE(source.findByKey("One"));

                                AND_THEN("THE TREE IS STILL BALANCED"){
                                    CHECK(source.isTreeBalanced());
                                }
                            }

                            AND_WHEN("REMOVING THE ELEMENT WITH ONE CHILD"){
                                source.erase("Six");
                                 CHECK(source.getNumOfElem() == 3);
                                //source.display();

                                THEN("THE DICTIONARY DOES NOT HAVE THAT ELEMENT"){
                                    CHECK(source.count(9) == 0);
                                    CHECK_FALSE(source.findByKey("Six"));

                                    AND_THEN("THE TREE IS STILL BALANCED"){
                                        CHECK(source.isTreeBalanced());
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


TEST_CASE("LOGIC PERATORS", "[dictionary]"){

    GIVEN("CREATING TWO INSTANCE OF DICTIONARY"){

        Dictionary<std::string, int> first;
        Dictionary<std::string, int> second;
        
        CHECK(first.isEmpty());
        CHECK(second.isEmpty());

        AND_GIVEN("INSERTING THE SAME ELEMENTS"){

            first.insert("Guitar", 7);
            first.insert("Trumpet", 3);
            first.insert("Violin", 1);
            first.insert("Drums", 9);

            second.insert("Guitar", 7);
            second.insert("Trumpet", 3);
            second.insert("Violin", 1);
            second.insert("Drums", 9);

            //first.display();
            CHECK(first.getNumOfElem() == 4);
            CHECK(second.getNumOfElem() == 4);

            CHECK(first.isTreeBalanced());
            CHECK(second.isTreeBalanced());

            THEN("THE TWO DICTIONARIES ARE THE SAME"){
                CHECK((first==second));
                CHECK_FALSE( (first != second) );

                AND_THEN("INSERTING ONE WORD TO THE first DICTIONARRY"){
                    first.insert("Fluet", 10);
                    first.display();

                    THEN("THE DICTIONARY first HAS ONE ELEMENT MORE THAN THE second"){
                        CHECK_FALSE( (first == second) );
                        CHECK( (first != second) );
                        CHECK( (first > second) );
                        CHECK( (second < first) );

                        AND_WHEN("INSERTING THE SAME ELEMENT TO THE second DICTIONARY"){
                            second.insert("Fluet", 10);

                            THEN("THE DICTIONARIES ARE THE SAME"){
                                CHECK( (first == second) );
                                
                                AND_THEN("DICTIONARIES HAVE THE SAME NUMBER OF ELEMENTS"){
                                    CHECK( (first >= second) );
                                    CHECK( (second <= first) );
                                    CHECK( (first.getNumOfElem() == second.getNumOfElem()) );

                                    AND_THEN("TREES ARE BALANCED"){
                                        //first.display();
                                        CHECK(first.isTreeBalanced());
                                        CHECK(second.isTreeBalanced());
                                        //first.display();

                                        AND_THEN("THE MINIMAL ELEMENT IS THE WORD DRUMS"){
                                            CHECK(first.getExtremum().first == "Drums");

                                            AND_THEN("MAXIMAL ELEMENT IS THE WORD - VIOLIN"){
                                                CHECK(first.getExtremum().second == "Violin");
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

TEST_CASE("OPERATORS OVERLOADNG", "[dictionary]"){


     GIVEN("CREATING TWO INSTANCE OF DICTIONARY"){

        Dictionary<std::string, int> first;
        Dictionary<std::string, int> second;
        Dictionary<std::string, int> third;
        
        CHECK(first.isEmpty());
        CHECK(second.isEmpty());
        CHECK(third.isEmpty());

        AND_GIVEN("INSERTING THE SAME ELEMENTS"){

            first.insert("Guitar", 7);
            first.insert("Trumpet", 3);
            first.insert("Violin", 1);
            first.insert("Harp", 12);
            first.insert("Banjo", 80);
            
            second.insert("Piano", 2);
           // second.display();
            second.insert("Xylophone", 6);
           // second.display();
            second.insert("Harp", 14);
            //second.display();
            second.insert("Clarinet", 11);
            //second.display();
            second.insert("Other", 15);
            //second.display();
            second.insert("Asomething", 17);
            //second.display();
            second.insert("Aasomething", 16);
            //second.display();
            second.insert("Jasomeword", 45);
            //second.display();
            second.insert("Iaword", 16);
            //second.display();

            CHECK(first.getNumOfElem() == 5);
            CHECK(second.getNumOfElem() == 9);

            CHECK(first.isTreeBalanced());

            CHECK(second.isTreeBalanced());
            
            AND_WHEN("USING THE OPERATOR +"){
                third = first + second;
                CHECK_FALSE(third.isEmpty());
                CHECK(third.getNumOfElem() == 13);

                THEN("THE third DICTIONARY SHOULD HAVE EVERY UNIQUE WORD FROM THE BOTH DICTIONARIES"){
                   CHECK(third.findByKey("Guitar"));
                   CHECK(third.findByKey("Trumpet"));
                   CHECK(third.findByKey("Violin"));
                   CHECK(third.findByKey("Harp"));
                   CHECK(third.findByKey("Banjo"));
                   CHECK(third.findByKey("Piano"));
                   CHECK(third.findByKey("Xylophone"));
                   CHECK(third.findByKey("Clarinet"));
                   CHECK(third.findByKey("Other"));

                   CHECK(third.isTreeBalanced());
                }
            }

            AND_WHEN("USING THE OPERATOR +="){

                first += second;

                THEN("THE first DICTIONARY SHOULD HAVE INCREASED IN NUMBER OF UNIQUES WORDS"){
                   
                   CHECK(first.getNumOfElem() == 13);

                   AND_THEN("THESE ELEMENTS SHOULD BE AS FOLLOW"){

                        CHECK(first.findByKey("Guitar"));
                        CHECK(first.findByKey("Trumpet"));
                        CHECK(first.findByKey("Violin"));
                        CHECK(first.findByKey("Harp"));
                        CHECK(first.findByKey("Banjo"));
                        CHECK(first.findByKey("Piano"));
                        CHECK(first.findByKey("Xylophone"));
                        CHECK(first.findByKey("Clarinet"));
                        CHECK(first.findByKey("Other"));
                        CHECK(first.findByKey("Aasomething"));
                        CHECK(first.findByKey("Jasomeword"));
                        CHECK(first.findByKey("Iaword"));
                        CHECK(first.findByKey("Asomething"));
                   }
                }

                THEN("CHECKING THE ELEMENTS WITH THE operator[]"){

                    CHECK(first["Banjo"] == 80);
                    CHECK(first["Guitar"] == 7);
                    CHECK(first["Trumpet"] == 3);
                    CHECK(first["Piano"] == 2);
                    CHECK(first["Harp"] == 12);
                    CHECK(first["Violin"] == 1);
                    CHECK(first["Xylophone"] == 6);
                    CHECK(first["Clarinet"] == 11);
                    CHECK(first["Other"] == 15);
                    CHECK(first["Aasomething"] == 16);
                    CHECK(first["Jasomeword"] == 45);
                    CHECK(first["Iaword"] == 16);
                    CHECK(first["Asomething"] == 17);

                    AND_THEN("THE MINIMAL ELEMENT IS Aasomething"){
                        CHECK(first.getExtremum().first == "Aasomething");

                        AND_THEN("THE MAXIMAL ELEMENTS IS Xylophone"){
                            CHECK(first.getExtremum().second == "Xylophone");
                        }
                    }
                }
            }
        }
     }
}


TEST_CASE("TESTING EXCEPTIONS", "[dictionary]"){

    GIVEN("CREATING EMPTY DICTIONARY"){

         Dictionary<std::string, int> source;
         CHECK(source.isEmpty());
         Dictionary<std::string, int> emptySource;
         CHECK(emptySource.isEmpty());

         WHEN("FINDING THE EXTREMUMS WHICH DO NOT EXISTS"){
             CHECK_THROWS_AS(source.getExtremum().first == "something", std::underflow_error);

            AND_WHEN("INSERTING THE SAME ELEMENT"){
                source.insert("Banana", 8);
                CHECK_THROWS_AS(source.insert("Banana", 18), std::overflow_error);

                AND_WHEN("GETTING THE INFO OF NON-EXISTING ELEMENT"){
                    CHECK_THROWS_AS(source["another"] == 19, std::underflow_error);

                    AND_WHEN("GETTING THE INFO FROM EMPTY DICTIONARY"){
                        CHECK_THROWS_AS(emptySource["another"] == 19, std::underflow_error);
                    }
                }
            }
         }
    }
}
TEST_CASE("CHECKING THE ITERATOR", "[dictionary]"){

    Dictionary<std::string, int> source;

    source.insert("Location", 4);
    source.insert("Great", 1);
    source.insert("Rooms", 2);
    source.insert("Staff", 14);
    source.insert("Service", 43);
    source.insert("Italian", 42);
    source.insert("One", 23);
    source.insert("Eat", 32);
    source.insert("Christmas", 71);
    source.insert("Wrangler", 66);
    source.insert("Apple", 76);
    source.insert("Zenit", 11);

    source.display();

    CHECK(source.isTreeBalanced());

    Dictionary<std::string, int>::Iterator it = source.begin();
    Dictionary<std::string, int>::Iterator newIter = source.begin();

    //operator==

    CHECK( (it == newIter) );

    CHECK( (*it) == "Rooms" );
    CHECK( it.getInfo() == 2 );

    //moving to the left
    CHECK(it.left());
    //operator!=
    CHECK( (it != newIter) );

    CHECK(it.getKey() == "Great");
    CHECK( it.getInfo() == 1 );

    //moving to the left
    CHECK(it.left());
    CHECK( (*it) == "Christmas");
    CHECK( it.getInfo() == 71);

    //moving to the right
    CHECK(it.right());
    CHECK( (*it) == "Eat");
    CHECK( it.getInfo() == 32);

    //moving iterator to the next element which is nullptr
    CHECK(it.right());
    CHECK_THROWS_AS( (it.getKey() == "Something") , std::underflow_error);
    //given iterator is at the moment nullptr
    CHECK_FALSE(it.left());

    //assigning the moved iterator to the first element
    it = newIter;
    CHECK( (*it) == "Rooms" );
    CHECK( it.getInfo() == 2 );

    //moving to the right       
    CHECK(it.right());
    CHECK( (*it) == "Staff");
    CHECK( it.getInfo() == 14);
}

TEST_CASE("CHECKING THE BALANCE OF THE TREE", "[dictionary]"){

    Dictionary<std::string, int> source;

    source.insert("Location", 4);
    source.insert("Great", 1);
    source.insert("Rooms", 2);
    source.insert("Staff", 14);
    source.insert("Service", 43);
    source.insert("Italian", 42);
    source.insert("One", 23);
    source.insert("Eat", 32);
    source.insert("Christmas", 71);
    source.insert("Wrangler", 66);
    source.insert("Apple", 76);
    source.insert("Zenit", 11);
    
    source.insert("Mistake", 42);
    source.insert("Cold", 23);
    source.insert("Familiar", 32);
    source.insert("Astonished", 71);
    source.insert("Fetch", 66);
    source.insert("path", 76);
    source.insert("king", 11);
    
    source.insert("copy", 42);
    source.insert("attack", 23);
    source.insert("mix", 32);
    source.insert("quiet", 71);
    source.insert("loyalty", 66);
    source.insert("seep", 76);
    source.insert("miserable", 11);

    CHECK(source.isTreeBalanced());

    //source.display();
}