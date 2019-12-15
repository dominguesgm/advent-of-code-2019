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

main :: IO ()
main = do
    inputHandler <- openFile "input.txt" ReadMode
    stringArray <- fileReadLoop inputHandler 
    let fractArray = map (read :: String -> Float) stringArray
    let fuelPerModule = map (calcFuel) fractArray
    let result = sum fuelPerModule
    
    putStrLn $ "Result: " ++ show result