#|
==================================================
-*- Mode: Lisp; Syntax: Common-Lisp; -*-
Module: gps.lisp: a lisp implementation of
Newell and Simon's GPS system.

Bugs to vladimir dot kulyukin at usu dot edu 
==================================================

MY PLAN OUTPUT

((START) (EXECUTE DROP-BALL) (EXECUTE PUSH-CHAIR-TO-BANANAS) (EXECUTE CLIMB-ON-CHAIR) (EXECUTE GRAB-BANANAS) (EXECUTE EAT-BANANAS))

and
[6]> (gps world-state-2 goal-2)
Goal: NOT-HUNGRY
Consider: EAT-BANANAS
  Goal: HAS-BANANAS
  Consider: GRAB-BANANAS
    Goal: CHAIR-AT-BANANAS
    Consider: PUSH-CHAIR-TO-BANANAS
      Goal: AT-DOOR
      Goal: ON-FLOOR
      Goal: HUNGRY
      Goal: HANDS-AVAILABLE
      Consider: DROP-BALL
        Goal: HUNGRY
        Goal: HAS-BALL
      Action: DROP-BALL
      Goal: CHAIR-AT-DOOR
    Action: PUSH-CHAIR-TO-BANANAS
    Goal: HUNGRY
    Goal: HANDS-AVAILABLE
    Goal: ON-CHAIR
    Consider: CLIMB-ON-CHAIR
      Goal: CHAIR-AT-BANANAS
      Goal: HUNGRY
      Goal: HANDS-AVAILABLE
      Goal: ON-FLOOR
    Action: CLIMB-ON-CHAIR
  Action: GRAB-BANANAS
Action: EAT-BANANAS
((START) (EXECUTE DROP-BALL) (EXECUTE PUSH-CHAIR-TO-BANANAS) (EXECUTE CLIMB-ON-CHAIR) (EXECUTE GRAB-BANANAS) (EXECUTE EAT-BANANAS))




|#

(in-package :user)

(require :auxfuns "auxfuns")

(defstruct op "An operation"
  (action nil) 
  (preconds nil) 
  (add-list nil) 
  (del-list nil))

(defun executing-p (x)
  "Is x of the form: (execute ...) ?"
  (starts-with x 'execute))

(defun convert-op (op)
  "Make op conform to the (EXECUTING op) convention."
  (unless (some #'executing-p (op-add-list op))
    (push (list 'execute (op-action op)) (op-add-list op)))
  op)

(defun op (action &key preconds add-list del-list)
  "Make a new operator that obeys the (EXECUTING op) convention."
  (convert-op
    (make-op :action action :preconds preconds
             :add-list add-list :del-list del-list)))

;;; ==============================

(defparameter *school-ops*
  (list
    (make-op :action 'drive-son-to-school
	     :preconds '(son-at-home car-works)
	     :add-list '(son-at-school)
	     :del-list '(son-at-home))
    (make-op :action 'shop-installs-battery
	     :preconds '(car-needs-battery shop-knows-problem shop-has-money)
	     :add-list '(car-works))
    (make-op :action 'tell-shop-problem
	     :preconds '(in-communication-with-shop)
	     :add-list '(shop-knows-problem))
    (make-op :action 'telephone-shop
	     :preconds '(know-phone-number)
	     :add-list '(in-communication-with-shop))
    (make-op :action 'look-up-number
	     :preconds '(have-phone-book)
	     :add-list '(know-phone-number))
    (make-op :action 'give-shop-money
	     :preconds '(have-money)
	     :add-list '(shop-has-money)
	     :del-list '(have-money))))

(mapc #'convert-op *school-ops*)

;;; ==============================

(defvar *ops* nil "A list of available operators.")

(defstruct op "An operation"
  (action nil) (preconds nil) (add-list nil) (del-list nil))

(defun GPS (state goals &optional (*ops* *ops*))
  "General Problem Solver: from state, achieve goals using *ops*."
  (remove-if #'atom (achieve-all (cons '(start) state) goals nil)))

;;; ==============================

(defun achieve-all (state goals goal-stack)
  "Achieve each goal, and make sure they still hold at the end."
  (let ((current-state state))
    (if (and (every #'(lambda (g)
                        (setf current-state
                              (achieve current-state g goal-stack)))
                    goals)
             (subsetp goals current-state :test #'equal))
        current-state)))

(defun achieve (state goal goal-stack)
  "A goal is achieved if it already holds,
  or if there is an appropriate op for it that is applicable."
  (dbg-indent :gps (length goal-stack) "Goal: ~a" goal)
  (cond ((member-equal goal state) state)
        ((member-equal goal goal-stack) nil)
        (t (some #'(lambda (op) (apply-op state goal op goal-stack))
                 (find-all goal *ops* :test #'appropriate-p)))))

;;; ==============================

(defun member-equal (item list)
  (member item list :test #'equal))

;;; ==============================

(defun apply-op (state goal op goal-stack)
  "Return a new, transformed state if op is applicable."
  (dbg-indent :gps (length goal-stack) "Consider: ~a" (op-action op))
  (let ((state2 (achieve-all state (op-preconds op) 
                             (cons goal goal-stack))))
    (unless (null state2)
      ;; Return an updated state
      (dbg-indent :gps (length goal-stack) "Action: ~a" (op-action op))
      (append (remove-if #'(lambda (x) 
                             (member-equal x (op-del-list op)))
                         state2)
              (op-add-list op)))))

(defun appropriate-p (goal op)
  "An op is appropriate to a goal if it is in its add list."
  (member-equal goal (op-add-list op)))

;;; ==============================

(defun use (oplist)
  "Use oplist as the default list of operators."
  ;; Return something useful, but not too verbose: 
  ;; the number of operators.
  (length (setf *ops* oplist)))

;;; ==============================


(defparameter *banana-ops*
  ;;; WRITE YOUR OPERATORS HERE (i.e., replace NIL with them)
  ;;; use the same syntax as in *school-ops* abovev.
  (list
    ;;; at-door on-floor has-ball hungry chair-at-door
    (make-op :action 'drop-ball
	     :preconds '(hungry has-ball)
	     :del-list '(has-ball)
       :add-list '(hands-available))
    ;;; at-door on-floor hands-available hungry chair-at-door
    (make-op :action 'push-chair-to-bananas
	     :preconds '(at-door on-floor hungry hands-available chair-at-door)
       :del-list '(at-door chair-at-door)
	     :add-list '(chair-at-bananas))
    ;;; on-floor hands-available hungry chair-at-bananas
    (make-op :action 'climb-on-chair
	     :preconds '(chair-at-bananas hungry hands-available on-floor)
       :del-list '(on-floor)
	     :add-list '(on-chair))
    ;;; hands-available hungry chair-at-bananas on-chair
    (make-op :action 'grab-bananas
	     :preconds '(chair-at-bananas hungry hands-available on-chair)
       :del-list '(hands-available)
	     :add-list '(has-bananas))
    ;;; hungry chair-at-bananas on-chair has-bananas
    (make-op :action 'eat-bananas
	     :preconds '(has-bananas)
       :del-list '(hungry)
       :add-list '(not-hungry)
    ;;; not-hungry chair-at-bananas on-chair has-bananas   
       ))
  )

(mapc #'convert-op *banana-ops*)

;;; ==============================

(defun trace-gps ()
  (do-debug :gps))

(defun untrace-gps ()
  (do-undebug))


