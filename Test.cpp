#include "doctest.h"
#include "FamilyTree.hpp"
using namespace family;

#include <string>
using namespace std;


TEST_CASE("Test add perants and finding them and give their relation") {
	family::Tree T("Joseph senior");	
	T.addFather("Joseph senior", "Avrham");
	T.addMother("Joseph senior", "Yafa");
	T.addFather("Avrham", "Joseph");
	T.addMother("Avrham", "Gizela");
	T.addFather("Yafa", "David");
	T.addMother("Yafa", "Hasmit");
	T.addFather("Joseph", "Zevi");
	T.addMother("Joseph", "Sara");
	CHECK(relation("Zevi") == string("great-grandfather"));
	CHECK(relation("David") == string("grandfather"));
	CHECK(relation("Joseph") == string("grandfather"));
	CHECK(relation("Yafa") == string("mother"));
	CHECK(relation("Gizela") == string("grandmother"));
	CHECK(relation("Sara") == string("great-grandmother"));
	CHECK(relation("Joseph senior") == string("me"));
	CHECK(relation("Avrham") == string("father"));
	CHECK(relation("Hasmit") == string("grandmother"));
	CHECK(relation("Shoki") == string("unrelated"));
}



TEST_CASE("Test add perants and finding them ant try to find them again after removing them") {
	family::Tree T("Joseph senior");	
	T.addFather("Joseph senior", "Avrham");
	T.addMother("Joseph senior", "Yafa");
	T.addFather("Avrham", "Joseph");
	T.addMother("Avrham", "Gizela");
	T.addFather("Yafa", "David");
	T.addMother("Yafa", "Hasmit");
	T.addFather("Joseph", "Zevi");
	T.addMother("Joseph", "Sara");
	CHECK(relation("Zevi") == string("great-grandfather"));
	T.remove("Zevi");	
	CHECK(T.relation("Zevi") == string("unrelated"));
	CHECK(T.relation("Joseph") == string("grandfather"));
	T.remove("Joseph");
	CHECK(T.relation("Yafa") == string("mother"));
	T.remove("Yafa");
	CHECK(T.relation("Yafa") == string("unrelated"));
	CHECK(T.relation("Gizela") == string("grandmother"));
	CHECK(T.relation("Sara") == string("unrelated"));
	CHECK(T.relation("Joseph senior") == string("me"));
	T.remove("Avrham");
	CHECK(T.relation("Avrham") == string("unrelated"));
	CHECK(relation("Hasmit") == string("unrelated"));
}



TEST_CASE("Test add perants and finding random relation") {
	family::Tree T("Joseph senior");	
	T.addFather("Joseph senior", "Avrham");
	T.addMother("Joseph senior", "Yafa");
	T.addFather("Avrham", "Joseph");
	T.addMother("Avrham", "Gizela");
	T.addFather("Yafa", "David");
	T.addMother("Yafa", "Hasmit");
	T.addFather("Joseph", "Zevi");
	T.addMother("Joseph", "Sara");
	T.addFather("Zevi", "Shoki");
	CHECK(relation("great-grandfather") == string("Zevi"));
	CHECK(relation("mother") == string("Yafa"));
	CHECK(relation("grandmother") == string("Gizela"));
	CHECK(relation("grandfather") == string("Joseph"));
	CHECK(relation("great-great-grandfather") == string("Shoki"));
	CHECK(relation("great-grandmother") == string("Sara"));
	T.remove("Joseph");	
	CHECK(relation("grandfather") == string("David"));
	CHECK(relation("me") == string("Joseph senior"));
	CHECK(relation("father") == string("Avrham"));
	T.remove("Gizela");
	CHECK(relation("grandmother") == string("Hasmit"));
	CHECK(relation("great-grandfather") == string("Zevi"));
}


TEST_CASE("Test add perants and finding random relation then change there names and check again if the relation is still the same") {
	family::Tree T("Joseph senior");	
	T.addFather("Joseph senior", "Avrham");
	T.addMother("Joseph senior", "Yafa");
	T.addFather("Avrham", "Joseph");
	T.addMother("Avrham", "Gizela");
	T.addFather("Yafa", "David");
	T.addMother("Yafa", "Hasmit");
	T.addFather("Joseph", "Zevi");
	T.addMother("Joseph", "Sara");
	T.addFather("Zevi", "Shoki");
	CHECK(relation("great-grandfather") == string("Zevi"));
	CHECK(relation("mother") == string("Yafa"));
	CHECK(relation("grandmother") == string("Gizela"));
	T.remove("Gizela");
	T.addMother("Avrham", "");
	CHECK(relation("grandfather") == string("Joseph"));
	CHECK(relation("great-great-grandfather") == string("Shoki"));
	CHECK(relation("great-grandmother") == string("Sara"));
	T.remove("Joseph");	
	CHECK(relation("grandfather") == string("David"));
	CHECK(relation("me") == string("Joseph senior"));
	CHECK(relation("father") == string("Avrham"));
	T.remove("Gizela");
	CHECK(relation("grandmother") == string("Hasmit"));
	CHECK(relation("great-grandfather") == string("Zevi"));
}




