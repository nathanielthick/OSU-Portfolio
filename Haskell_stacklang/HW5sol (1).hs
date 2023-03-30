-- --------------------------------------
-- Nathaniel Thickett
-- CS 381
-- HW5 Types
-- --------------------------------------
module HW5sol where
import Data.Maybe
import HW5types


-- --------------------------------------
-- RankC
-- returns CMD rank tuple of form (input, output)
-- --------------------------------------
rankC :: Cmd -> CmdRank
rankC (LDB i) = (0,1)
rankC (LDI i) = (0,1)
rankC ADD = (2,1)
rankC MULT = (2,1)
rankC DUP = (1,2)
rankC DEC = (1,1)
rankC SWAP = (2,2)
rankC LEQ = (2,1)
rankC (POP i) = (i,0)

rankC (IFELSE p1 p2) = (r, o)
  where
    o1 = inputs p1 +1
    o2 = inputs p2 +1
    i1 = outputs p1
    i2 = outputs p2
    r = (max o1 o2)
    o = (min i1 i2)

-- --------------------------------------
-- inputs
-- returns INT value of total rank of input using recursion
-- --------------------------------------
inputs :: Prog -> Int
inputs [] = 0
inputs (d:ds) =
  let (inputCount, outputCount) = rankC d
  in inputCount + inputs ds

-- --------------------------------------
-- outputs
-- returns INT value of total rank of output using recursion
-- --------------------------------------
outputs :: Prog -> Int
outputs [] = 0
outputs (d:ds) =
  let (inputCount, outputCount) = rankC d
  in outputCount + outputs ds

-- --------------------------------------
-- rankP
-- returns either Rank Value, or Nothing in the case of RankError
-- --------------------------------------
rankP :: Prog -> Rank -> Maybe Rank
rankP [] r = Just r
rankP (p:ps) r =  let (a,b) = rankC p in
		 if a > r then Nothing else if a == -1 then Nothing else if b == -1 then Nothing else rankP ps ((r-a)+b)


-- --------------------------------------
-- convert
-- converts result "A stack" to Maybe Stack for use in semCmd recursion
-- --------------------------------------
convert :: Result -> Maybe Stack
convert (A s) =  Just(s) 
convert (TypeError) =  Nothing
convert (RankError) =  Nothing





-- --------------------------------------
-- semCmd
-- takes CMD and applies it to the stack passed to it
-- --------------------------------------
semCmd :: Cmd ->Stack -> Maybe Stack

-- loads bool val to stack
semCmd (LDB n) s =  Just ((B n):s) 
-- loads int val to stack
semCmd (LDI n) s =  Just ((I n):s) 

-- swaps top two stack values
semCmd SWAP (s:a:ss) = Just (a:s:ss)
semCmd SWAP [] = Just []

-- POPs first k values from stack using recursion
semCmd (POP 1) (s:ss) = Just (ss)

semCmd (POP k) (s:ss) =
    if k <= length (s:ss) then
        semCmd (POP (k-1)) ss
    else
        Nothing
semCmd (POP 0) _ = Nothing
semCmd (POP k) [] = Nothing

-- Multiples first two values in stack(must be int)
semCmd MULT [] = Nothing
semCmd MULT ((I x):[]) = Nothing
semCmd MULT ((I x):(I y):s) = Just ((I(x*y)):s)
semCmd MULT _ = Nothing

-- decrements first value in stack(must be int)
semCmd DEC ((I x):s) = Just (I (x-1):s)
semCmd DEC ((B x):s) = Nothing
semCmd DEC [] = Nothing

-- duplicates first element of stack
semCmd DUP [] = Nothing
semCmd DUP ((I x):s) = Just ((I x):(I x):s)
semCmd DUP ((B x):s) = Just ((B x):(B x):s)

-- Adds first two elements of stack, must be type INT
semCmd ADD [] = Nothing
semCmd ADD ((I x):[]) = Nothing
semCmd ADD ((I x):(I y):s) = Just ((I(x+y)):s)
semCmd ADD _ = Nothing

-- performs <= operation on first two items in stack, replaces them with Bool t/f
semCmd LEQ [] = Nothing
semCmd LEQ ((I x):[]) = Nothing
semCmd LEQ ((I x):(I y):s) = Just ((B (x<=y)):s)
semCmd LEQ _ = Nothing

-- runs first prog if top of stack is true Bool value, second prog if false Bool value
semCmd (IFELSE [] []) (s:ss) = convert(run [] (ss))
semCmd (IFELSE (x:xs) (y:ys)) ((I s):ss) = Nothing
semCmd (IFELSE (x:xs) (y:ys)) ((B s):ss) = 
  if s then convert(run (x:xs) (ss))
  else convert(run (y:ys) (ss))

semCmd (IFELSE (x:xs) []) ((B s):ss) = 
  if s then convert(run (x:xs) (ss))
  else convert(run [] (ss))



-- --------------------------------------
-- run
-- first uses rankP to check for rank errors, if none, runs the prog passed on the stack passed
-- --------------------------------------
run :: Prog -> Stack -> Result
run [] s = A s
run (c:cs) s =
  case rankP (c:cs) (length s) of
        Nothing -> RankError 
        Just r' ->  -- if no rank errors, continue to run
            case semCmd c s of
                Nothing -> TypeError
                Just s' -> -- if no type errors, continue to run
                    case run cs s' of
                        RankError -> RankError
                        TypeError -> TypeError
                        res -> res


