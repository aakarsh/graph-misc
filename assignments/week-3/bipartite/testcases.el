(setq an/testsuites
 (cons 
  (make-an/testsuite
   :name "bipartite"
   :dir "/home/aakarsh/src/c++/coursera/graphs/assignments/week-3/bipartite"
   :testcases
  (list
   (make-an/testcase  
    :name "simple-1"
    :lines '(
             "4 4"
             "1 2"
             "4 1"
             "2 3"
             "3 1")    
    :cmd "bipartite"
    :ans "0")

   (make-an/testcase  
    :name "simple-2"
    :lines '(             
             "5 4"
             "5 2"
             "4 2"
             "3 4"
             "1 4")    
    :cmd "bipartite"
    :ans "0")))
  an/testsuites))

