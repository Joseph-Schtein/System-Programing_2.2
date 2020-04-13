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

//10

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

//11

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
//11

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

//9

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
	
}














