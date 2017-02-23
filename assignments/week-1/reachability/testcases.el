(setq an/testsuites
 (cons 
  (make-an/testsuite
   :name "reachability"
   :dir "/home/aakarsh/src/c++/graphs/assignments/week-1/reachability"
   :testcases
  (list
   (make-an/testcase  
    :name "simple-1"
    :lines '(
             "4 4"
             "1 2"
             "3 2"
             "4 3"
             "1 4"
             "1 4")
    
    :cmd "reachability"
    :ans "0")

   (make-an/testcase  
    :name "simple-2"
    :lines '(             
             "4 2"
             "1 2"
             "3 2"
             "1 4")
    
    :cmd "reachability"
    :ans "0")))
  an/testsuites))

