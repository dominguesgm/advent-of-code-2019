import System.IO

fileReadLoop :: Handle -> IO [String]
fileReadLoop handle = do 
    ineof <- hIsEOF handle
    if ineof
        then return []
        else do
            inpStr <- hGetLine handle
            futureVal <- (fileReadLoop handle)
            return ((:) inpStr futureVal)

calcFuel :: Float -> Integer
calcFuel weight = floor (weight / 3) - 2

accFuel :: Float -> Integer
accFuel weight = let fuel = calcFuel weight in
    if fuel > 0
        then fuel + accFuel(fromInteger(fuel))  
        else 0

main :: IO ()
main = do
    inputHandler <- openFile "input.txt" ReadMode
    stringArray <- fileReadLoop inputHandler 
    let fractArray = map (read :: String -> Float) stringArray
    let fuelPerModule = map (accFuel) fractArray
    let result = sum fuelPerModule
    
    putStrLn $ "Result: " ++ show result