#!/bin/bash

while [ 1 ]
do
  echo "-----------------------------"
  echo "Enter the first number:"
  read num1
  echo "Enter the second number:"
  read num2

  echo "Enter the choice:"
  echo "1) ADDITION"
  echo "2) SUBTRACTION"
  echo "3) MULTIPLICATION"
  echo "4) DIVISION"
  echo "5) EXIT"

  read choice

  case $choice in
    1)
      result=$(echo "$num1 + $num2" | bc)
      echo "Result: $result"
      ;;
    2)
      result=$(echo "$num1 - $num2" | bc)
      echo "Result: $result"
      ;;
    3)
      result=$(echo "$num1 * $num2" | bc)
      echo "Result: $result"
      ;;
    4)
      if [ "$num2" -eq 0 ]; then
        echo "Error: Division by zero is not allowed!"
      else
        result=$(echo "scale=2; $num1 / $num2" | bc)
        echo "Result: $result"
      fi
      ;;
    5)
      echo "Exiting calculator. Goodbye!"
      break
      ;;
    *)
      echo "Invalid choice! Please enter a number between 1 and 5."
      ;;
  esac
done

