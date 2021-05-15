#|
===========================================================
-*- Mode: Lisp; Syntax: Common-Lisp -*-

File: ca-loader.lisp

Bugs to vladimir kulyukin in canvas.
===========================================================
|#

(in-package :user)

;;; change this to the directory where the ca files are.
(defparameter *ca-dir* "/mnt/c/dev/CS6600/Homework/hw10/ca_sam/")

(defparameter *files* '("ca-utilities" "cd" "ca" "ca-functions" "ca-lexicon"))

(defun ca-loader (files &key (mode :lisp))
  (dolist (a-file files t)
    (load (concatenate 'string
            *ca-dir*
            a-file
            (ecase mode
              (:lisp ".lisp")
              (:cl  ".cl")
              (:fasl ".fasl"))))))
