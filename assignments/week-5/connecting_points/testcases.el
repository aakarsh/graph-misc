(setq an/testsuites
 (cons 
  (make-an/testsuite
   :name "connecting_points"
   :dir "/home/aakarsh/src/c++/coursera/graphs/assignments/week-5/connecting_points"
   :testcases
  (list
   (make-an/testcase  
    :name "simple-1"
    :lines '(
             "4"
             "0 0"
             "0 1"
             "1 0"
             "1 1")
    :cmd "connecting_points"
    :ans "3")

   (make-an/testcase  
    :name "simple-2"
    :lines '(
             "5"
             "0 0"
             "0 2"
             "1 1"
             "3 0"
             "3 2")    
    :cmd "connecting_points"
    :ans "7.064495102")))
  an/testsuites))

