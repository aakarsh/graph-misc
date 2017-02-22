(defstruct an/testcase name lines cmd  ans)
(defstruct an/testsuite name testcases dir)
(defvar an/testsuites '())

(defun an/load-suites()
  (let ((testcase-files (find-lisp-find-files default-directory ".*testcases.el$")))
    (setq an/testsuites nil)
    (dolist (f testcase-files)
      (load-file f))))

(defun an/run-suite(name)
  (interactive "sTestsuite Name:")
  (an/load-suites)
  (dolist(ts an/testsuites)
    (if (and (an/testsuite-p ts)
             (equal name (an/testsuite-name ts)))
        (an/run-testsuite ts))))

(defun an/run-test(test)
  (with-temp-buffer
    (mapcar
     (lambda(line)
       (insert (format "%s\n" line)))
     (an/testcase-lines test))
    (shell-command-on-region
     (point-min)
     (point-max)
     (format  "%s/%s 2> %s" default-directory
              (an/testcase-cmd test)
              (format "%s/result-%s.log" default-directory (an/testcase-name test)))

     nil t)
    (buffer-string)))

(defun an/run-testsuite(ts)
  (let ((all-passed t)
        (default-directory (an/testsuite-dir ts)))
    (dolist (test (an/testsuite-testcases  ts))
      (let* ((ans (an/testcase-ans test))
             (result (an/run-test test))
            (name (an/testcase-name test)))
        (if (not (equal ans  result))
            (progn
              (message "Failed:%s->[%s] but was [%s]" name ans result)
              (setq all-passed  nil)))))
    (if all-passed
        (message "All tests passed !"))))




