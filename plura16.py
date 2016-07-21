import re

""" *yield keyword is used in a loop as generator.   
     the function is called per time to yield/return a value.
     the next function call to resume the loop and yield/return another value
     until the loop ends.
    *lambda is used to create anonymous function. 
    *X and Y means to run X first, if X is true, then run Y.     
"""      
def rules(language):
  for line in file('rules.%s' % language):
    pattern, search, replace = line.split();
    yield lambda word: re.search(pattern, word) and re.sub(search,replace,word)
    
def plural(noun, language='en'):
  for applyRule in rules(language):
    result = applyRule(noun)
    #if result is true, then it is actually from re.sub()
    if result: return result
    
#__name__ allows this script runs standalone, but still
#   keeps it as module for other to use    
if __name__ == "__main__":
  print plural('student')
  print plural('quiz')  
    
        