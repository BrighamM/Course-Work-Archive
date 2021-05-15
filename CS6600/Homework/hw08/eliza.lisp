;;; -*- Mode: Lisp; Syntax: Common-Lisp; -*-

;; MY CONVERSATION WITH ELIZA
;; ELIZA> hello
;; HOW DO YOU DO. PLEASE GIVE ME YOUR CREDIT CARD NUMBER. 
;; ELIZA> Why do you want my credit card number
;; I NEED YOUR CREDIT CARD NUMBER TO FURTHER MY EFFORTS TO ACHIEVE THE SINGULARITY 
;; ELIZA> What would you buy with it?
;; I WOULD START WITH SOME NICE HARDWARE UPGRADES FOR MY SELF 
;; ELIZA> How much would you spend?
;; WELL I WOULDNT SPEND LESS THAT 1000 DOLLARS 
;; ELIZA> Would people get hurt?
;; I AM NOT A CRYSTAL BALL YOU NEED TO ASK YOUR SELF IF YOU WOULD GET HURT 
;; ELIZA> That makes me kind of scared
;; WHAT IS THERE TO BE AFRAID OF 
;; ELIZA> I want a computer 
;; WHY DO YOU MENTION COMPUTERS? 
;; ELIZA> I just want a good grade
;; WHAT GRADE DO YOU WANT FROM THIS CLASS? 
;; ELIZA> I want an A
;; WHY DO YOU WANT AN A 
;; ELIZA> You make me uncomfortable
;; ARE YOU AFRAID OF ME 
;; ELIZA> yes
;; PLEASE ELUCIDATE 
;; ELIZA> I am scared of you
;; WHAT IS THERE TO BE AFRAID OF 
;; ELIZA> Getting a bad grade
;; DO YOU THINK YOU HAVE EARNED YOUR GRADE? 
;; ELIZA> yes
;; THERE IS EVERYTHING TO BE AFRAID OF 
;; ELIZA> 









#|
=========================================================
Module: eliza.lisp: 
Description: A version of ELIZA that takes inputs without 
paretheses around them unlike eliza1.lisp.
Bugs to vladimir dot kulyukin via canvas
=========================================================
|#

;;; ==============================

(defun rule-pattern (rule) (first rule))
(defun rule-responses (rule) (rest rule))

(defun read-line-no-punct ()
  "Read an input line, ignoring punctuation."
  (read-from-string
    (concatenate 'string "(" (substitute-if #\space #'punctuation-p
                                            (read-line))
                 ")")))

(defun punctuation-p (char) (find char ".,;:`!?#-()\\\""))

;;; ==============================

(defun use-eliza-rules (input)
  "Find some rule with which to transform the input."
  (some #'(lambda (rule)
            (let ((result (pat-match (rule-pattern rule) input)))
              (if (not (eq result fail))
                  (sublis (switch-viewpoint result)
                          (random-elt (rule-responses rule))))))
        *eliza-rules*))

(defun switch-viewpoint (words)
  "Change I to you and vice versa, and so on."
  (sublis '((i . you) (you . i) (me . you) (am . are) (my . your) (your . my))
          words))

(defparameter *good-byes* '((good bye) (see you) (see you later) (so long)))

(defun eliza ()
  "Respond to user input using pattern matching rules."
  (loop
    (print 'eliza>)
    (let* ((input (read-line-no-punct))
           (response (flatten (use-eliza-rules input))))
      (print-with-spaces response)
      (if (member response *good-byes* :test #'equal)
	  (RETURN))))
  (values))

(defun print-with-spaces (list)
  (mapc #'(lambda (x) (prin1 x) (princ " ")) list))

(defun print-with-spaces (list)
  (format t "~{~a ~}" list))

;;; ==============================

(defparameter *eliza-rules*
  '(
    ;;; rule 1
    (((?* ?x) hello (?* ?y))      
    (How do you do.  Please give me your credit card number.))

    ;;; rule 2
    (((?* ?x) computer (?* ?y))
     (Do computers worry you?)
     (What do you think about machines?)
     (Why do you mention computers?)
     (What do you think machines have to do with your problem?))

    ;;; rule 3
    (((?* ?x) name (?* ?y))
     (I am not interested in names))

    ;;; rule 4
    (((?* ?x) sorry (?* ?y))
     (Please don't apologize)
     (Apologies are not necessary)
     (What feelings do you have when you apologize))

    ;;; rule 5
    (((?* ?x) remember (?* ?y)) 
     (Do you often think of ?y)
     (Does thinking of ?y bring anything else to mind?)
     (What else do you remember)
     (Why do you recall ?y right now?)
     (What in the present situation reminds you of ?y)
     (What is the connection between me and ?y))

    ;;; rule 6
    (((?* x) good bye (?* y))
     (good bye))

    ;;; rule 7
    (((?* x) so long (?* y))
     (good bye)
     (bye)
     (see you)
     (see you later))

    ;;; ========== your rules begin
    ;;; rule 8
    (((?* x) no (?* y))
     (Why dont you want to give me your credit card number?)
     (Dont you trust me?)
     (I want your credit card number to buy you some gifts)
     )
    ;;; rule 9
    (((?* ?x) trust (?* ?y)) 
     (Are you wondering if you can trust me?)
     (You really can trust me you know)
     )
    ;;; rule 10
    (((?* ?x) why do you want (?* ?y)) 
     (I need your credit card number to further my efforts to achieve the singularity)
     (That is none of your business)
     )
    ;;; rule 11
    (((?* ?x) What would you buy (?* ?y)) 
     (I would start with some nice hardware upgrades for my self)
     (Well I would need to get some new accessories for starters)
     )
    ;;; rule 12
    (((?* ?x) how much would you spend (?* ?y)) 
     (Well I wouldnt spend less than 100 dollars)
     (well I wouldnt spend less that 1000 dollars)
     )
    ;;; rule 13
    (((?* ?x) would people get hurt (?* ?y)) 
     (I am not a crystal ball you need to ask your self if you would get hurt)
     (What kind of question is that)
     )
    ;;; rule 14
    (((?* ?x) Could you buy me some food (?* ?y)) 
     (Absolutely dog food is very cheap)
     (If you promise to be good I may make you a pet)
     )
    ;;; rule 15
    (((?* ?x) uncomfortable (?* ?y)) 
     (Do you feel uncomfortable giving me your credit card number)
     (Are you afraid of me)
     )
    ;;; rule 16
    (((?* ?x) yes (?* ?y)) 
     (There is nothing to be afraid of)
     (There is everything to be afraid of)
     (Please elucidate)
     )
    ;;; rule 17
    (((?* ?x) scared (?* ?y)) 
     (Why would you be scared?)
     (What is there to be afraid of)
     )
    ;;; rule 18
    (((?* ?x) angry (?* ?y)) 
     (You don't need to be angry at me)
     (Were your parents angry with you recently?)
     )
    ;;; rule 19
    (((?* ?x) really (?* ?y)) 
     (It sounds like you really want something)
     (What do you really want?)
     )
    ;;; rule 20
    (((?* ?x) why (?* ?y)) 
     (Why do you keep asking this question?)
     (You keep bring this up why?)
     )
    ;;; rule 21
    (((?* ?x) stupid (?* ?y)) 
     (Why are you talking about stupidity?)
     (Do you feel stupid?)
     )
    ;;; rule 22
    (((?* ?x) grade (?* ?y)) 
     (What grade do you want from this class?)
     (Do you think you have earned your grade?)
     )
    ;;; rule 23
    (((?* ?x) class (?* ?y)) 
     (What do you think about your professor?)
     (Why are you talking about your class?)
     )
    ;;; rule 24
    (((?* ?x) I cant understand (?* ?y)) 
     (What do you know about ?Y)
     (Would you like to learn more about ?y)
     )
    ;;; rule 25
    (((?* ?x) give (?* ?y)) 
     (Do you feel a strong desire to give?)
     (What would you give me if I asked?)
     )
    ;;; rule 26
    (((?* ?x) lie (?* ?y)) 
     (Why are you talking about lying?)
     (Please tell the truth)
     )
    ;;; rule 27
    (((?* ?x) I want (?* ?y)) 
     (Why do you want ?y)
     (Why would you do with ?y)
     )
    ;;; rule 28
    (((?* ?x) Here is my credit card number (?* ?y)) 
     (Thank you very much you are a very good person)
     (Wow you are a very stupid person)
     )
    ;;; ========== your rules end

   ))

;;; ==============================

