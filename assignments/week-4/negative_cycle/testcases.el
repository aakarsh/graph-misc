(setq an/testsuites
 (cons 
  (make-an/testsuite
   :name "negative_cycle"
   :dir "/home/aakarsh/src/c++/graphs/assignments/week-4/negative_cycle"
   :testcases
  (list
   (make-an/testcase  
    :name "one-negative-cycle"
    :lines '(
             "4 4"
             "1 2 -5"
             "4 1 2"
             "2 3 2"
             "3 1 1")
    :cmd "./negative_cycle"
    :ans "1")

   (make-an/testcase  
    :name "disconnected-graph"
    :lines '(
             "5 4"
             "1 2 1"
             "3 4 -1"
             "4 5 -1"
             "5 3 1")    
    :cmd "./negative_cycle"
    :ans "1")

   (make-an/testcase  
    :name "non-negative-cycle-disconnected-graph-2"
    :lines '(
             "5 4"
             "1 2 1"
             "3 4 1"
             "4 5 1"
             "5 3 1")    
    :cmd "./negative_cycle"
    :ans "0")

   (make-an/testcase  
    :name "non-negative-cycle-disconnected-graph-3"
    :lines '(
             "5 4"
             "1 2 1"
             "3 4 -1"
             "4 5 1"
             "5 3 1")    
    :cmd "./negative_cycle"
    :ans "0")


   (make-an/testcase  
    :name "non-negative-cycle-disconnected-graph-4"
    :lines '(
             "5 4"
             "1 2 -1"
             "3 4 -1"
             "4 5 1"
             "5 3 1")    
    :cmd "./negative_cycle"
    :ans "0")

   (make-an/testcase  
    :name "non-negative-cycle-5"
    :lines '(
             "4 5"
             "1 2 1"
             "2 3 1"
             "3 4 1"
             "4 1 1"
             "2 4 -1")    
    :cmd "./negative_cycle"
    :ans "0")

   (make-an/testcase  
    :name "non-negative-cycle-6"
    :lines '(
             "2 2"
             "1 2 -1"
             "2 1 1"
             )    
    :cmd "./negative_cycle"
    :ans "0")

   (make-an/testcase  
    :name "negative-cycle-7"
    :lines '(
             "2 2"
             "1 2 -1"
             "2 1 -1"
             )    
    :cmd "./negative_cycle"
    :ans "1")

   (make-an/testcase  
    :name "negative-cycle-7"
    :lines '(
             "4 4"
             "1 2 1"
             "2 1 -1"
             "3 4 -2"
             "4 3 1"
             )    
    :cmd "./negative_cycle"
    :ans "1")

   (make-an/testcase  
    :name "no-edges-1"
    :lines '(
             "5 0"
             )    
    :cmd "./negative_cycle"
    :ans "0")


   (make-an/testcase  
    :name "no-no-cycle-negative-acycliec"
    :lines '(
             "5 4"
             "1 2 -1"
             "4 2 -1"
             "3 2 -1"
             "4 5 -1"
             )    
    :cmd "./negative_cycle"
    :ans "0")


   
   
   ))
  
  an/testsuites))

