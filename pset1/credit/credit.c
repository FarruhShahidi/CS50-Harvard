#include <cs50.h>
#include<stdio.h>
#include<math.h>

int main(void)
  
{   
  // I need the number of digits
  int num_digits = 0; 
  // I need the number the first two digits
  int first_digit = 0, second_digit = 0;
  // store 2*(second-to-last) + the_rest in total
  int total = 0;
  // get cc number
  long copy = get_long("Enter you cc number:\n");
  
  
  while (copy > 0)
  {
    // what are the current two digits?
    // if we are at the last of the while loop then copy%10 is the first digit.
    // what about the second digit? In this while loop we keep updating first_digit =copy %10. Note that in the last step before the while loop stops, first_digits is actually second_digit before we update its value, so here we go
    second_digit = first_digit;
    first_digit = copy % 10;
    // If we double every other digit from second-to-last digit then at the time of doubling num_digits is odd
    if (num_digits % 2 == 1)
    {
      int temp = 2 * first_digit;
      total += temp % 10 + (temp / 10);
    }
    else
    {
      total += first_digit;
    }
    
    // a counting num_digits
    num_digits++;
    // and go to the next digit
    copy /= 10;
  }
  // combine the first two digits
  int first_two_digits = first_digit * 10 + second_digit;
  // Now that we have the number of digits, the first two digits, and the total sum we make inferences
  if (total % 10 == 0 && num_digits >= 13 && num_digits <= 16 && first_digit == 4)
  {
    printf("VISA\n");
  }
  else if (total % 10 == 0 && num_digits == 15 && num_digits <= 16 && (first_two_digits == 34 || first_two_digits == 37))
  {
    printf("AMEX\n");
  }
  
  else if (total % 10 == 0 && num_digits == 16 && first_two_digits >= 51 && first_two_digits <= 55)
  {
    printf("MASTERCARD\n");
  }
  else
  {
    printf("INVALID\n");
    
  }
  
  
}
