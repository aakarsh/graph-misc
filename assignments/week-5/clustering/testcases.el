(setq an/testsuites
 (cons 
  (make-an/testsuite
   :name "clustering"
   :dir "/home/aakarsh/src/c++/coursera/graphs/assignments/week-5/clustering"
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
    :cmd "clustering"
    :ans "3.000000000")

   (make-an/testcase  
    :name "simple-2"
    :lines '(
             "5"
             "0 0"
             "0 2"
             "1 1"
             "3 0"
             "3 2")    
    :cmd "clustering"
    :ans "7.064495102")))
  an/testsuites))

