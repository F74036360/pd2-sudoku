# pd2-sudoku
我出題是先用一個設好的數獨陣列做轉換，其中可以做列行轉換，宮交換位置，還有數字++
解題是把空格位置先找出來然後每+一次1都去看有沒有跟宮列行重複的，若沒重複則暫存，但因為這樣子可能會導致後面錯誤，所以當後面
的格子+到9還是不能過時表前面存錯，將原本存空格位置的陣列-1就可以指道上一個空格的地方，再去遞回，若144個位置都跑完還是不能
過表此為無解數獨，傳0。找到第一個解後再去側有沒有第二個解的可能，我是用反測法，將空格在重新設0，從最後一個格子開始找，若這樣子
出來的答案根本來的依樣代表唯一解，不一樣則為多重解。
