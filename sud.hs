import Control.Applicative
import Data.List
import Data.Maybe

type Board = [Int]

sameRow i j = div i 9 == div j 9
sameCol i j = mod (i - j) 9 == 0
sameBlock i j = div i 27 == div j 27 && div (mod i 9) 3 == div (mod j 9) 3

shouldExclude i j = sameRow i j || sameCol i j || sameBlock i j

getExcluded :: Int -> Board -> [Int]
getExcluded i board = nub $ map (board !!) $ filter (shouldExclude i) [0..80]

replaceIdx :: Int -> Int -> Board -> Board
replaceIdx i m board = (take i board) ++ [m] ++ (drop (i+1) board)

allReplacements :: Int -> Board -> [Board]
allReplacements i board = map (\j -> replaceIdx i j board) allowed
    where excluded = getExcluded i board
          allowed = filter (\n -> not (elem n excluded)) [1..9]

fromStr :: String -> Board
fromStr s = map (read . (:"")) s :: [Int]

findZero :: Board -> Maybe Int
findZero = elemIndex 0

next :: Board -> Maybe [Board]
next board = (\i -> allReplacements i board) <$> findZero board

solved :: Board -> Bool
solved = isNothing . findZero

deadEnd :: Board -> Bool
deadEnd b = (not . solved) b && (null . fromJust . next) b

next' :: Board -> Maybe [Board]
next' b = filter (not . deadEnd) <$> next b

solve :: Board -> Maybe Board
solve b | solved b = Just b
        | deadEnd b = Nothing
        | otherwise = getSolved $ map solve $ fromJust $ next' b

getSolved :: [Maybe Board] -> Maybe Board
getSolved [] = Nothing
getSolved (x:xs) = case solved <$> x of
    Just True -> x
    _ -> getSolved xs

printBoard :: Board -> IO ()
printBoard [] = return ()
printBoard xs = print (take 9 xs) >> printBoard (drop 9 xs)

main :: IO ()
main = do
    s <- getLine
    (printBoard . fromJust . solve . fromStr) s