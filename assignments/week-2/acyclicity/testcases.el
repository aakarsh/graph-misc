(setq an/testsuites
 (cons 
  (make-an/testsuite
   :name "acyclicity"
   :dir "/home/aakarsh/src/c++/graphs/assignments/week-2/acyclicity"
   :testcases
  (list
   (make-an/testcase  
    :name "simple-1"
    :lines '(
             "5 7"
             "1 2"
             "2 3"
             "1 3"
             "3 4"
             "1 4"
             "2 5"
             "3 5")
    :cmd "acyclicity"
    :ans "0")

   (make-an/testcase  
    :name "simple-2"
    :lines '(
             "4 3"
             "3 2"
             "1 2"
             "4 3")
    
    :cmd "acyclicity"
    :ans "0")

   (make-an/testcase  
    :name "simple-3"
    :lines '(
             "4 6"
             "1 2"
             "3 2"
             "4 3"
             "4 2"
             "1 3"
             "1 4")    
    :cmd "acyclicity"
    :ans "0")

   (make-an/testcase  
    :name "simple-4"
    :lines '(
             "4 4"
             "1 2"
             "4 1"
             "2 3"
             "3 1")    
    :cmd "acyclicity"
    :ans "1")


   (make-an/testcase  
    :name "simple-5"
    :lines '(
             "3 3"
             "1 2"
             "3 2"
             "2 1")    
    :cmd "acyclicity"
    :ans "1")

   (make-an/testcase  
    :name "simple-6"
    :lines '(
             "4 7"
             "1 2"
             "3 2"
             "4 3"
             "4 2"
             "3 1"
             "1 4")    
    :cmd "acyclicity"
    :ans "1")
   ))
  an/testsuites))

