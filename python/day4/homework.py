'''
@Author: Ru_j
@Date: 2020-03-05 17:57:27
@LastEditors: Ru_j
@LastEditTime: 2020-03-05 19:57:35
@Description:
'''


class Students:
    def __init__(self):
        self.stus = []

    def print_stus(self):
        if len(self.stus) == 0:
            print("No students info here")
        for stu in self.stus:
            print("Name: {} Age: {} Gender: {}"
                  .format(stu['name'], stu['age'], stu['gender']))

    def insert_stu(self, name, age, gender):
        if isinstance(age, str) and not age.isdigit() or int(age) <= 0:
            return False
        if isinstance(age, int) and age <= 0:
            return False
        if gender.capitalize() not in ['Male', 'Female']:
            return False
        for std in self.stus:
            if std['name'] == name:
                return False
        self.stus.append({'name': name, 'age': age,
                          'gender': gender.capitalize()})
        return True

    def delete_stu(self):
        name = input("Input a name: ")
        for stu in self.stus:
            if stu['name'] == name:
                self.stus.remove(stu)
                return True
        return False

    def find_stu(self):
        name = input("Input a name: ")
        for stu in self.stus:
            if stu['name'] == name:
                print("Name: {} Age: {} Gender: {}"
                      .format(stu['name'], stu['age'], stu['gender']))
                return
        print("Not Fount")
        return False

    def update_stu(self):
        index = input("Input a index: ")
        if not index.isdigit():
            print("Invalid index")
            return False
        if index.isdigit() and int(index) > len(self.stus):
            print("Out of range")
            return False
        index = int(index)
        new_name = input("input a new name: ")
        new_age = input("input a new age: ")
        if new_age != '' and not new_age.isdigit():
            print("Age must be numbers")
            return False
        if new_age != '' and int(new_age) <= 0:
            print("Age must be positive numbers")
            return False
        new_gender = input("input a new gender: ").capitalize()
        if new_gender not in ["Male", "Female", ""]:
            print("Gender only be male and female")
            return False
        old_info = list(self.stus[index].values())
        self.stus[index]['name'] = new_name if new_name != "" else old_info[0]
        self.stus[index]['age'] = new_age if new_age != "" else old_info[1]
        self.stus[index]['gender'] = new_gender if new_gender != "" else \
            old_info[2]

    def run(self):
        print("""
            ----- Students Manage System -----
            [1] Print Infos
            [2] Insert Student's Info
            [3] Search Student's Info
            [4] Update Student's Info
            [5] Delete Student's Info
            [6] Quit

            Input Your Choice:
            ----------------------------------
        """, end="")
        choose = input()
        if choose == '1':
            self.print_stus()
        elif choose == '2':
            name = input("Input name: ")
            age = input("Input age: ")
            gender = input("Input gender: ")
            self.insert_stu(name, age, gender)
        elif choose == '3':
            self.find_stu()
        elif choose == '4':
            self.update_stu()
        elif choose == '5':
            self.delete_stu()
        elif choose == '6':
            exit()
        else:
            self.run()


if __name__ == "__main__":
    my_stus = Students()
    my_stus.insert_stu('one', 15, 'male')
    my_stus.insert_stu('two', 20, 'female')
    while True:
        my_stus.run()
