(setq an/testsuites
 (cons 
  (make-an/testsuite
   :name "toposort"
   :dir (pwd)
   :testcases
  (list
   (make-an/testcase  
    :name "simple-1"
    :lines '(
             "4 3"
             "1 2"
             "4 1"
             "3 1")    
    :cmd "toposort"
    :ans "4 3 1 2")

   (make-an/testcase  
    :name "simple-2"
    :lines '(
             "4 1"
             "3 1")
    
    :cmd "toposort"
    :ans "4 3 2 1")


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
    :cmd "toposort"
    :ans "5 4 3 2 1")


   ))
  an/testsuites))

