#### PART 1 ####
# final_grade: Calculates the final grade for each student, and writes the output (while eliminating illegal
# rows from the input file) into the file in `output_path`. Returns the average of the grades.
#   input_path: Path to the file that contains the input
#   output_path: Path to the file that will contain the output


def final_grade(input_path: str, output_path: str) -> int:
    """
    final_grade: Calculates the final grade for each student, and writes the output (while eliminating illegal
    rows from the input file) into the file in `output_path`.
    :param input_path: Path to the file that contains the input
    :param output_path: Path to the file that will contain the output
    :return: Average final grades if legal rows were found, zero otherwise.
    """
    avg_final_grades = 0
    grades_data = create_grades_data(input_path)
    grades_to_file(output_path, grades_data)
    if grades_data:
        final_grades = list(map(lambda data: data["student_final_grade"], grades_data.values()))
        avg_final_grades = int(sum(final_grades) / len(grades_data))
    return avg_final_grades


def create_grades_data(input_path: str) -> dict:
    """
    create_grades_data: Do the following foreach student in input file:
    - Eliminating illegal rows from the input file (see: `is_valid_input`).
    - If row is legal, creates grades data of student, consisted of:
        - unique id (last record in file)
        - homework_avg
        - student_final_grade
    :param input_path:
    :return: grades_data
    """
    separator = ','
    student_data_keys = ['name', 'semester', 'homework_avg']
    grades_data = dict()
    with open(input_path) as input_file:
        lines = input_file.readlines()
    for line in lines:
        input_data_values = list(filter(lambda char: char != separator, line.split(separator)))
        input_data_values = list(map(str.strip, input_data_values))
        student_id = input_data_values[0].strip()
        student_data_values = input_data_values[1:]
        student_data = dict(zip(student_data_keys, student_data_values))
        if is_legal_line_data(student_id, student_data):
            homework_avg = int(student_data["homework_avg"])
            student_final_grade = calculate_final_grade(student_id, homework_avg)
            grades_data[student_id] = {"homework_avg": homework_avg,
                                       "student_final_grade": student_final_grade}
    return grades_data


def grades_to_file(output_path: str, grades_data: dict):
    """
    grades_to_file: Writes grades data into txt file.
    :param output_path: Path of file to write into
    :param grades_data: Grades data dict to write from
    :return:
    """
    with open(output_path, 'w') as output_file:
        for student_id, grades_data in sorted(grades_data.items()):
            student_str = "{student_id}, {homework_avg}, {student_final_grade}\n". \
                format(student_id=student_id,
                       homework_avg=grades_data["homework_avg"],
                       student_final_grade=grades_data["student_final_grade"])
            output_file.write(student_str)


def is_legal_line_data(student_id: str, student_data: dict) -> bool:
    """
    is_legal_line: Check if a given data of line if it's legal, as follows:
    - Id has 8 digits and can't start with 0.
    - Name is consisted of [A-Za-z] and spaces only
    - Semester is bigger or equal to 1
    - Average grades is bigger than 50 and at most 100
    :param student_id: Id of the student to check
    :param student_data: Data of student: <name (string)>, <semester (int)>, <homework avg (int)>
    :return:
    """
    valid_min_grade = 50
    valid_max_grade = 100
    valid_id_len = 8
    valid_min_semester = 1
    return all([
        len(str(student_id)) == valid_id_len,
        int(str(student_id)[0]) != 0,
        student_data.get('name').replace(' ', '').isalpha(),
        int(student_data.get('semester')) >= valid_min_semester,
        valid_min_grade < int(student_data.get('homework_avg')) <= valid_max_grade
    ])


def calculate_final_grade(student_id: str, homework_avg: int) -> int:
    """
    calculate_final_grade: Calculate final grade for a given student:
    (two last digits of id + homework_avg) / 2.
    :param homework_avg: Average homework of the student
    :param student_id: Id of the student
    :return: final grade
    """
    return int((int(student_id[-2:]) + homework_avg) / 2)


#### PART 2 ####
# check_strings: Checks if `s1` can be constructed from `s2`'s characters.
#   s1: The string that we want to check if it can be constructed
#   s2: The string that we want to construct s1 from
def check_strings(s1: str, s2: str) -> bool:
    letters = list(char for char in s2.lower())
    for letter in s1.lower():
        if letter in letters:
            letters.remove(letter)
        else:
            return False
    return True
