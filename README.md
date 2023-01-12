# Words-Frequency-Data-Structure
One of my final assignments for my Data Structure course

1.	Description of the Solution
In this section, you shall briefly describe the problem that you had to solve. Then describe how you solved the problem and what data structures you used.
The problem I have to solve is to calculate and store the top 100 words in a context and list them in a readable order.
First, I have to open the file the teacher used and read the content inside
Second, I need to identify whether the words are alphas or not, then count the number of the alphas 
Third, decided by the numbers of upper 100 words, replace each of them comparing to each other if some of them are bigger
Four, use a main function that includes a hash and a binary tree to store the words mentioned above
Five, print out the results in a readable form.
2.	Analysis of the Solution Program
In this section, you shall give the times it took to process the example input files. If the outputs deviate from given outputs, try to figure out why. If you use additional input files, describe them here.
For example, take Ulysses and War And Peace(I think the right name is this) as an example(since they were my beloved books).
  ![image](https://user-images.githubusercontent.com/102947704/212070105-cb953a61-f25e-4118-8cf4-d4023cc14819.png)

Then, War And Peace:
   ![image](https://user-images.githubusercontent.com/102947704/212070138-98b59044-29b7-4768-b6db-4f6676003742.png)

Then, according to obtained results, try to estimate, how many words and how big a file your program can process in 15 seconds. Other analysis is not required but is allowed.
First Ulysses, Because the reaction time is 0.124s and processed 267,643 words and 1,537KB, then if 15s is considered, the words it can process would be 32,376,169 words and 18,156 M
Second War And Peace, Because the reaction time is 0.25s and processed 569,769 words and 3,152KB, then if 15s is considered, the words it can process would be 34,186,140 words and 18,468M
