rm final_result.out
for i in {1..100}
do
  echo "Test(" $i ") ................................................. :-" >> final_result.out
  ./caltrain
  ./caltrain >> final_result.out
done
