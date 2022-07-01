{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}

{-# HLINT ignore "Use camelCase" #-}
fizzbuzz :: Int -> String
fizzbuzz x = (if x `mod` 3 == 0 then "fizz" else "") ++ (if x `mod` 5 == 0 then "buzz" else "")

multiParam :: Int -> Int -> Int -> Int
multiParam a b c = a * b + c
