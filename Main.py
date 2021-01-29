import re
import os
import tarfile
import subprocess
from subprocess import Popen, PIPE, STDOUT


# filters out all src files(a1-a4)
def regular_expression_filter():
    id_index = -1
    source_list = ['csc344/a1/main.c', 'csc344/a2/core.clj', 'csc344/a3/Main.scala', 'csc344/a4/project4_2.pl',
                   'csc344/a5/Project5.py']
    identifier_list = ['csc344/a1/identifiers_a1', 'csc344/a2/identifiers_a2', 'csc344/a3/identifiers_a3',
                       'csc344/a4/identifiers_a4', 'csc344/a5/identifiers_a5']
    # loops through each directory getting the source file
    for current_dir in source_list:
        id_index = id_index + 1
        # opening file
        with open(current_dir) as file_object:
            file = file_object.read()

        # filters out unwanted symbols
        new_file1 = re.sub(r"[-(),;={}<>+\]!|/&#?%*.:'[]", " ", file)
        new_file2 = re.sub(r"\".+\"", "", new_file1)
        new_file3 = re.sub(r"//.+", "", new_file2)
        new_file4 = re.sub(r"#.+", "", new_file3)
        new_file5 = re.sub(r"\t", "", new_file4)

        # writes the filtered file to the text file
        with open(identifier_list[id_index], 'w') as w:
            w.write(new_file5)

        # reads the text file
        with open(identifier_list[id_index], 'r') as r:
            lines_list = r.readlines()

        # splits the list read from the text file
        stripped_list = []
        for x in lines_list:
            stripped_list.append(x.split())

        # takes the split list and creates a new list
        inside_list = []
        with open(identifier_list[id_index], "w") as f:
            for item in stripped_list:
                for i in item:
                    inside_list.append(i)
                    f.write("%s\n" % i)

        # removes duplicates and sorts the list
        inside_list_set = set(inside_list)
        inside_list_no_dup = list(inside_list_set)
        # sorts the lists
        inside_list_no_dup.sort()
        with open(identifier_list[id_index], 'w') as x:
            for line in inside_list_no_dup:
                x.write(line + '\n')


# gets number of lines for each src code (calls wc)
def get_lines(directory_name):
    result = subprocess.run(['wc', '-l', directory_name], stdout=subprocess.PIPE, encoding='utf-8')
    var = result.stdout
    num_of_lines = var[:3]
    name = var[13:]
    return name + " Number of lines: " + num_of_lines


# creates html for each summary_ai.html file
def create_html(source_path, identifier_path, html_path, num_lines):
    html = """
        <html>
		    <head>
				    <title>Summary</title>
		    </head>

		    <body>
				    <h1>Summary</h1>
				    <a href={identifier_path}>Identifiers</a>
                    <p></p>
                    <a href={source_path}>{source_path}</a>
                    <br><br><p>{num_lines}</p><br>
		    </body>
    </html>
    """.format(identifier_path=identifier_path, source_path=source_path, num_lines=num_lines)

    with open(html_path, 'w') as w:
        w.write(html)


# creates tar file
def create_tar(path, tar_name):
    with tarfile.open(tar_name, "w:gz") as tar_handle:
        tar_handle.add(path, arcname=os.path.basename(path))


# sends mail to given email
def send_email(tar_file):
    email_address = input("Enter an email address: ")
    a = subprocess.Popen('echo "Hello! Here is my project" | mutt -s "CSC344 project 5" {email_address} -a "{tar_file}"'.format(email_address=email_address,
                                                                                 tar_file=tar_file), shell=True)
    a.communicate()


# calls each function
regular_expression_filter()

html_paths = ['csc344/a1/summary_a1.html', 'csc344/a2/summary_a2.html', 'csc344/a3/summary_a3.html',
              'csc344/a4/summary_a4.html', 'csc344/a5/summary_a5.html']
source_list = ['csc344/a1/main.c', 'csc344/a2/core.clj', 'csc344/a3/Main.scala', 'csc344/a4/project4_2.pl',
               'csc344/a5/Project5.py']
source_code_paths = ['main.c', 'core.clj', 'Main.scala', 'project4_2.pl', 'Project5.py']
identifier_paths = ['identifiers_a1', 'identifiers_a2', 'identifiers_a3', 'identifiers_a4', 'identifiers_a5']
index = 0
for i in source_code_paths:
    create_html(i, identifier_paths[index], html_paths[index], get_lines(source_list[index]))
    index = index + 1


create_tar('./csc344', 'project5.tar.gz')
send_email("project5.tar.gz")
