import Numeric.LinearAlgebra




main = do
  a <- getLine
  let n = 320
  b <- getMat n
  let c = subMatrix (0,1) (n,3)$fromRows (map (fromList . map toEnum) b)::Matrix R
  saveMatrix "tr.csv" "%.0f," (tr c)


getInts = do
  x <- getLine
  let y = (map$toInt)$words (map (\y -> if y == ','then ' 'else y) x)
  return y
  where
    toInt x = read x ::Int
getMat x
  |x==1 = do
     y <- getInts
     return [y]
  |otherwise = do
     y <- getInts
     z <- getMat (x-1)
     let w = [y] ++ z
     return w

