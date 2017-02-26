(setq an/testsuites
 (cons 
  (make-an/testsuite
   :name "connected_components"
   :dir "/home/aakarsh/src/c++/graphs/assignments/week-1/connected_components"
   :testcases
  (list
   (make-an/testcase  
    :name "simple-1"
    :lines '(
             "4 2"
             "1 2"
             "3 2")
    
    :cmd "connected_components"
    :ans "2")

   (make-an/testcase  
    :name "simple-2"
    :lines '(
             "4 3"
             "1 2"
             "3 2"
             "4 3")    
    
    :cmd "connected_components"
    :ans "1")


   (make-an/testcase  
    :name "simple-3"
    :lines '(
             "5 7"
             "2 1"
             "3 2"
             "3 1"
             "4 3"
             "4 1"
             "5 2"
             "5 3")    
    :cmd "connected_components"
    :ans "1")


   ))
  an/testsuites))

