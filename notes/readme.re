###############################
#regular expression summary
###############################

 ^       matches the beginning of a string.
 $       matches the end of a string.
 \b      matches a word boundary.
 \d      matches any numeric digit.
 \D      matches any non-numeric character.
 x?      matches an optional x character (in other words, it matches an x zero or one times).
 x*      matches x zero or more times.
 x+      matches x one or more times.
 x{n,m}  matches an x character at least n times, but not more than m times.
 (a|b|c) matches either a or b or c.
 [abc]   matches exactly one of characters, a or b or c.
 [^abc]  matches any single character except a, b, or c”
 (x)     in general is a remembered group. You can get the value of what matched 
         by using the groups() method of the object returned by re.search.


###############################
#regular expression examples
###############################

>>> import re
>>> s = '100 NORTH BROAD ROAD'
"""  ^  means "beginning of the string"
     $  means "end of the string"
     +  means "one or more"
     *  means "zero or more"
     replace ending 'ROAD' in s to 'RD.'
"""
      
>>> re.sub('ROAD$', 'RD.', s)
'100 NORTH BROAD RD.'
"""  \b    means "a word boundary must occur right here"   
     \d    means "any numeric digit" (0 through 9)
    r'\t'  a raw string with prefix r. '\t' is a tab character. but r'\t' really 
           is the backslash character \ followed by the letter t.  
"""

>>> s = '100 BROAD'
>>> re.sub('\\bROAD$', 'RD.', s)  #or use r'\bROAD$'
'100 BROAD'
"""the '\' character in a string must itself be escaped
"""

>>> pattern = '^M?M?M?$'    #OR    pattern = '^M{0,3}$'
>>> re.search(pattern, 'M')
>>> re.search(pattern, 'MM')
>>> re.search(pattern, 'MMM')
>>> re.search(pattern, '')
"""  M?  to optionally match a single M character. Hence, an empty string or a string with
         one to three 'M's match the pattern. re.search() returns an object. 
         For all other strings, re.search() returns None to indicate no match found.
"""
         
>>> pattern = '^M?M?M?(CM|CD|D?C?C?C?)$'
"""  |  in parentheses, three mutually exclusive patterns separately by vertical bars.
"""

##########################################
#Regular expressions with inline comments
##########################################

>>> pattern = """
    ^                   # beginning of string
    M{0,4}              # thousands - 0 to 4 M's
    (CM|CD|D?C{0,3})    # hundreds - 900 (CM), 400 (CD), 0-300 (0 to 3 C's),
                        #            or 500-800 (D, followed by 0 to 3 C's)
    (XC|XL|L?X{0,3})    # tens - 90 (XC), 40 (XL), 0-30 (0 to 3 X's),
                        #        or 50-80 (L, followed by 0 to 3 X's)
    (IX|IV|V?I{0,3})    # ones - 9 (IX), 4 (IV), 0-3 (0 to 3 I's),
                        #        or 5-8 (V, followed by 0 to 3 I's)
    $                   # end of string
    """
>>> re.search(pattern, 'M', re.VERBOSE)                
<_sre.SRE_Match object at 0x008EEB48>
>>> re.search(pattern, 'MCMLXXXIX', re.VERBOSE)        
<_sre.SRE_Match object at 0x008EEB48>
>>> re.search(pattern, 'MMMMDCCCLXXXVIII', re.VERBOSE) 
<_sre.SRE_Match object at 0x008EEB48>
>>> re.search(pattern, 'M')   #This does not match. because it does not have the 
                              # re.VERBOSE flag. python treats the pattern as a
                              # compact regular expression.                         


#####################################
# Finding numbers
#####################################

>>> phonePattern = re.compile(r'^(\d{3})-(\d{3})-(\d{4})$') 
>>> phonePattern.search('800-555-1212').groups()       
('800', '555', '1212')
>>> phonePattern = re.compile(r'(\d{3})\D*(\d{3})\D*(\d{4})\D*(\d*)$') 
>>> phonePattern.search('work 1-(800) 555.1212 #1234').groups()        
('800', '555', '1212', '1234')
"""  \d       means "any numeric digit" (0 through 9)
     \d+      means "one or more digits"
     \D       means "any character except a numeric digit"
     \D+      means "one or more characters that are not digits"
     \D*      means "zero or more characters that are not digits"
     (\d{3})  Putting it in parentheses means “match exactly three numeric digits, 
              and then remember them as a group that I can ask for later”
     The groups() method above returns a tuple of elements, since the regular 
     expression now defines number of groups to remember.          
"""              

#implemented by re.VERBOSE
>>> phonePattern = re.compile(r'''
                # don't match beginning of string, number can start anywhere
    (\d{3})     # area code is 3 digits (e.g. '800')
    \D*         # optional separator is any number of non-digits
    (\d{3})     # trunk is 3 digits (e.g. '555')
    \D*         # optional separator
    (\d{4})     # rest of number is 4 digits (e.g. '1212')
    \D*         # optional separator
    (\d*)       # extension is optional and can be any number of digits
    $           # end of string
    ''', re.VERBOSE)
>>> phonePattern.search('work 1-(800) 555.1212 #1234').groups()       
('800', '555', '1212', '1234')
>>> phonePattern.search('800-555-1212')                     
('800', '555', '1212', '')

#####################################
# () a remembered group
#####################################
>>> re.sub('([^aeiou])y$', r'\1ies', 'vacancy') 
'vacancies'
"""
  re.sub      python re substitute function
  ([^aeiou])  put the matches in the remembered group, which is ('c') 
              in the above case
  \1          the first element in the remembered group, which is c
              hence, this example replaces 'cy$' with 'cies'.              
"""

