#include "doctest.h"
#include "FamilyTree.hpp"
using namespace family;

#include <string>
using namespace std;

//10

TEST_CASE("test add and relation") {
	Tree T("Joseph junior");	
	T.addFather("Joseph junior", "Avrham")
	.addFather("Avrham", "Joseph")
	.addMother("Avrham", "Gizela")
	.addFather("Joseph", "Zevi")
	.addMother("Joseph", "Sara");
	T.addMother("Joseph junior", "Yafa")
	.addFather("Yafa", "David")
	.addMother("Yafa", "Hasmit");
	CHECK(T.relation("Zevi") == "great-grandfather");
	CHECK(T.relation("David") == "grandfather");
	CHECK(T.relation("Joseph") == "grandfather");
	CHECK(T.relation("Yafa") == "mother");
	CHECK(T.relation("Gizela") == "grandmother");
	CHECK(T.relation("Sara") == "great-grandmother");
	CHECK(T.relation("Joseph junior") == "me");
	CHECK(T.relation("Avrham") == "father");
	CHECK(T.relation("Hasmit") == "grandmother");
	CHECK(T.relation("Shoki") == "unrelated");
}

//20

TEST_CASE("Test add perants and finding them ant try to find them again after removing them") {
	Tree T("Joseph junior");	
	T.addFather("Joseph junior", "Avrham")
	.addFather("Avrham", "Joseph")
	.addMother("Avrham", "Gizela")
	.addFather("Joseph", "Zevi")
	.addMother("Joseph", "Sara");
	T.addMother("Joseph junior", "Yafa")
	.addFather("Yafa", "David")
	.addMother("Yafa", "Hasmit");
	CHECK(T.relation("Zevi") == "great-grandfather");
	T.remove("Zevi");	
	CHECK(T.relation("Zevi") == "unrelated");
	CHECK(T.relation("Joseph") == "grandfather");
	T.remove("Joseph");
	CHECK(T.relation("Yafa") == "mother");
	T.remove("Yafa");
	CHECK(T.relation("Yafa") == "unrelated");
	CHECK(T.relation("Gizela") == "grandmother");
	CHECK(T.relation("Sara") == "unrelated");
	CHECK(T.relation("Joseph junior") == "me");
	T.remove("Avrham");
	CHECK(T.relation("Avrham") == "unrelated");
	CHECK(T.relation("Hasmit") == "unrelated");
}

//31

TEST_CASE("Test add perants and finding random relation") {
	Tree T("Joseph junior");	
	T.addFather("Joseph junior", "Avrham")
	.addMother("Joseph junior", "Yafa")
	.addFather("Avrham", "Joseph")
	.addMother("Avrham", "Gizela")
	.addFather("Yafa", "David")
	.addMother("Yafa", "Hasmit")
	.addFather("Joseph", "Zevi")
	.addMother("Joseph", "Sara")
	.addFather("Zevi", "Shoki");
	CHECK(T.find("great-grandfather") == string("Zevi"));
	CHECK(T.find("mother") == string("Yafa"));
	CHECK(T.find("grandmother") == string("Gizela"));
	CHECK(T.find("grandfather") == string("Joseph"));
	CHECK(T.find("great-great-grandfather") == string("Shoki"));
	CHECK(T.find("great-grandmother") == string("Sara"));
	T.remove("Joseph");	
	CHECK(T.find("grandfather") == string("David"));
	CHECK(T.find("me") == string("Joseph junior"));
	CHECK(T.find("father") == string("Avrham"));
	T.remove("Gizela");
	CHECK(T.find("grandmother") == string("Hasmit"));
	CHECK_THROWS(T.find("great-grandfather"));
}
//42

TEST_CASE("Test add perants and finding random relation then change there names and check again if the relation is still the same") {
	Tree T("Joseph senior");	
	T.addFather("Joseph senior", "Avrham")
	.addMother("Joseph senior", "Yafa")
	.addFather("Avrham", "Joseph")
	.addMother("Avrham", "Gizela")
	.addFather("Yafa", "David")
	.addMother("Yafa", "Hasmit")
	.addFather("Joseph", "Zevi")
	.addMother("Joseph", "Sara")
	.addFather("Zevi", "Shoki");
	CHECK(T.find("great-grandfather") == "Zevi");
	CHECK(T.find("mother") == "Yafa");
	CHECK(T.find("grandmother") == "Gizela");
	T.remove("Gizela");
	T.addMother("Avrham", "Leha");
	CHECK(T.find("grandfather") == "Joseph");
	CHECK(T.find("great-great-grandfather") == "Shoki");
	CHECK(T.find("great-grandmother") == "Sara");
	T.remove("Joseph");	
	CHECK(T.find("grandfather") == "David");
	CHECK(T.find("me") == "Joseph senior");
	CHECK(T.find("father") == "Avrham");
	T.remove("Leha");
	CHECK(T.find("grandmother") == "Hasmit");
	CHECK_THROWS(T.find("great-grandfather"));
}

//53

TEST_CASE("Test add perants and finding random relation then change there names and check again if the relation is still the same") {
	family::Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov")  
	.addMother("Yosef", "Rachel")  
	.addFather("Yaakov", "Isaac")
	.addMother("Yaakov", "Rivka")
	.addFather("Rachel", "Lavan")
	.addMother("Rachel", "Adina")
	.addFather("Isaac", "Avraham")
	.addMother("Isaac", "Sara")
	.addFather("Rivka","Betuel")
	.addFather("Sara","Heran")	
	.addFather("Avraham", "Terah");
	CHECK(T.find("grandmother") == "Rivka");
	CHECK(T.find("great-grandmother") == "Sara");
	CHECK(T.find("great-great-grandfather") == "Terah");
	CHECK(T.find("great-grandfather") == "Avraham");
	T.remove("Avraham");
	CHECK(T.find("great-grandfather") == "Betuel");
	T.remove("Yaakov");
	CHECK(T.find("grandfather") == "Lavan");
	CHECK(T.relation("Lavan") == "grandfather");
	CHECK(T.relation("Yaakov") == "unrelated");
	T.addFather("Yosef","Yaakov");
	CHECK(T.relation("Yaakov") == "father");
	CHECK(T.relation("Yosef") == "me");	
	T.remove("Yosef");
	CHECK(T.relation("Yosef") == "unrelated");
}

//60

TEST_CASE("I want to chack now if it throw errors as needed") {
	family::Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov")  
	.addMother("Yosef", "Rachel")  
	.addFather("Yaakov", "Isaac")
	.addMother("Yaakov", "Rivka")
	.addFather("Rachel", "Lavan")
	.addMother("Rachel", "Adina")
	.addFather("Isaac", "Avraham")
	.addMother("Isaac", "Sara")
	.addFather("Rivka","Betuel")
	.addFather("Sara","Heran")	
	.addFather("Avraham", "Terah");
	CHECK_THROWS(T.find("great-great-great-grandfather"));
	CHECK_THROWS(T.find("great-great-grandmother"));
	CHECK_THROWS(T.find("great-grandmther"));
	CHECK_THROWS(T.find("sister"));
	CHECK_THROWS(T.find("fathrs"));
	CHECK_THROWS(T.find("brother"));
	CHECK_THROWS(T.find("mothr"));
}

//70

TEST_CASE("Just random test") {
	family::Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov")  
	.addMother("Yosef", "Rachel")  
	.addFather("Yaakov", "Isaac")
	.addMother("Yaakov", "Rivka")
	.addFather("Rachel", "Lavan")
	.addMother("Rachel", "Adina")
	.addFather("Isaac", "Avraham")
	.addMother("Isaac", "Sara")
	.addFather("Rivka","Betuel")
	.addFather("Sara","Heran")	
	.addFather("Avraham", "Terah");
	CHECK(T.find(T.relation("Yosef")) == "Yosef");
	CHECK(T.find(T.relation("Rivka")) == "Rivka");	
	CHECK(T.find(T.relation("Lavan")) == "Isaac");//because it's first check the father side and than mother side	
	CHECK(T.find(T.relation("Avraham")) == "Avraham");
	CHECK(T.find(T.relation("Terah")) == "Terah");	
	CHECK(T.find(T.relation("Isaac")) == "Isaac");
	T.remove("Lavan");	
	CHECK_THROWS(T.find(T.relation("Lavan")));
	T.remove("Isaac");
	CHECK_THROWS(T.find(T.relation("Avraham")));
	T.remove("Yaakov");
	CHECK_THROWS(T.find(T.relation("Rivka")));
	T.remove("Yosef");
	CHECK_THROWS(T.find(T.relation("Yosef")));	
}

//80

TEST_CASE("Just random test") {
	family::Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov")  
	.addMother("Yosef", "Rachel")  
	.addFather("Yaakov", "Isaac")
	.addMother("Yaakov", "Rivka")
	.addFather("Rachel", "Lavan")
	.addMother("Rachel", "Adina")
	.addFather("Isaac", "Avraham")
	.addMother("Isaac", "Sara")
	.addFather("Rivka","Betuel")
	.addFather("Sara","Heran")	
	.addFather("Avraham", "Terah");
	CHECK(T.relation(T.find("me")) == "me");
	CHECK(T.relation(T.find("grandmother")) == "grandmother");	
	CHECK(T.relation(T.find("grandfather")) == "grandfather");	
	CHECK(T.relation(T.find("great-grandfather")) == "great-grandfather");
	CHECK(T.relation(T.find("great-great-grandfather")) == "great-great-grandfather");	
	CHECK(T.relation(T.find("mother")) == "mother");
	T.remove("Lavan");
	T.remove("Isaac");
	T.remove("Rivka");
	CHECK_THROWS(T.relation(T.find("grandfather")));
	CHECK_THROWS(T.relation(T.find("great-grandfather")));
	CHECK(T.relation(T.find("father")) == "father");
	T.remove("Yosef");
	CHECK(T.relation(T.find("me")) == "me");
}

//90

TEST_CASE("Just random test") {
	family::Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov")  
	.addMother("Yosef", "Rachel")  
	.addFather("Yaakov", "Isaac")
	.addMother("Yaakov", "Rivka")
	.addFather("Rachel", "Lavan")
	.addMother("Rachel", "Adina")
	.addFather("Isaac", "Avraham")
	.addMother("Isaac", "Sara")
	.addFather("Rivka","Betuel")
	.addFather("Sara","Heran")	
	.addFather("Avraham", "Terah");
	CHECK_THROWS(T.find(T.find("me")));
	CHECK_THROWS(T.find(T.find("father")));
	CHECK_THROWS(T.find(T.find("mother")));
	CHECK_THROWS(T.find(T.find("grandmother")));
	CHECK_THROWS(T.find(T.find("great-grandfather")));
	CHECK(T.relation(T.relation("Lavan")) == "unrelated");
	CHECK(T.relation(T.relation("Isaac")) == "unrelated");
	CHECK(T.relation(T.relation("Sara")) == "unrelated");
	CHECK(T.relation(T.relation("Terah")) == "unrelated");
	CHECK(T.relation(T.relation("Yosef")) == "unrelated");

}


TEST_CASE("Just random test") {
	family::Tree T ("Yosef"); 
	T.addFather("Yosef", "Yaakov")  
	.addMother("Yosef", "Rachel")  
	.addFather("Yaakov", "Isaac")
	.addMother("Yaakov", "Rivka")
	.addFather("Rachel", "Lavan")
	.addMother("Rachel", "Adina")
	.addFather("Isaac", "Avraham")
	.addMother("Isaac", "Sara")
	.addFather("Rivka","Betuel")
	.addFather("Sara","Heran")	
	.addFather("Avraham", "Terah");
	CHECK_THROWS(T.find(T.find("me")));
	CHECK_THROWS(T.find(T.find("father")));
	CHECK_THROWS(T.find(T.find("mother")));
	CHECK_THROWS(T.find(T.find("grandmother")));
	CHECK_THROWS(T.find(T.find("great-grandfather")));
	CHECK(T.relation(T.relation("Lavan")) == "unrelated");
	CHECK(T.relation(T.relation("Isaac")) == "unrelated");
	CHECK(T.relation(T.relation("Sara")) == "unrelated");
	CHECK(T.relation(T.relation("Terah")) == "unrelated");
	CHECK(T.relation(T.relation("Yosef")) == "unrelated");

}








