XAPIAN_CONFIG := ../../xapian-svn/xapian-core/xapian-config

CAnalyzer: CAnalyzer.cpp BinaryDictionary.cc compiledic.cc DBinaryDictionary.cpp dictionary.cc DoubleHashDictionary.cc FirstLevelDictionary.cc HashDictionary.cc PrepareDictionaries.cc SecondMapDictionary.cc utf8itor.cc BinaryDictionary.h compiledic.h DBinaryDictionary.h dictionary.h DoubleHashDictionary.h FirstLevelDictionary.h HashDictionary.h PrepareDictionaries.h resource.h SecondMapDictionary.h unicode.h visibility.h
	test -f stdafx.h || touch stdafx.h
	libtool --mode=link g++ -O2 `$(XAPIAN_CONFIG --cxxflags)` -W -Wall -o CAnalyzer `ls -1 *.cc|grep -v '^test\.cc'` CAnalyzer.cpp DBinaryDictionary.cpp `$(XAPIAN_CONFIG) --ltlibs`

test: BinaryDictionary.cc compiledic.cc DBinaryDictionary.cpp dictionary.cc DoubleHashDictionary.cc FirstLevelDictionary.cc HashDictionary.cc PrepareDictionaries.cc SecondMapDictionary.cc test.cc utf8itor.cc BinaryDictionary.h compiledic.h DBinaryDictionary.h dictionary.h DoubleHashDictionary.h FirstLevelDictionary.h HashDictionary.h PrepareDictionaries.h resource.h SecondMapDictionary.h unicode.h visibility.h
	test -f stdafx.h || touch stdafx.h
	libtool --mode=link g++ -O2 `$(XAPIAN_CONFIG --cxxflags)` -W -Wall -o test *.cc DBinaryDictionary.cpp `$(XAPIAN_CONFIG) --ltlibs`

clean:
	rm -f CAnalyzer test
