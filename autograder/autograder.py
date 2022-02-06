#!/usr/bin/env python3

import sys
import os
import shutil
import subprocess

submissionsDir = "submissions"
if len(sys.argv) != 2:
    print("assuming submissions are in ./submissions.  Pass submissions directory in argv to specify")
else:
    submissionsDir = sys.argv[1]


testValues = [0, #1 based indexing, ignore this
              4,
              28,
              8,
              4,
              16,
              8,
              8,
              4
              ]
# 4 points per instruction tested, basically
    
expectedLines = [0,
                  1,
                 9,
                 10,
                 11,
                 2,
                 7,
                 2,
                 9,
    ]

results = []

    
for file in os.listdir(submissionsDir):
    if file.endswith('.c'):
        student = file.split('_')[0]
        print(student)

        studentScore = 0
        
        shutil.rmtree("work", ignore_errors=True)
        shutil.copytree("release", "work")
        shutil.copy(os.path.join(submissionsDir,file), "work/assignment1.c")
        os.chdir("work")

        makeRes = subprocess.run(['make', 'testBitwiseFunctions'], capture_output=True)
        if makeRes.returncode != 0:
            print("bitwise tests didn't compile: Skipping the tests" )
            print(makeRes.stdout)
            print(makeRes.stderr)
            os.chdir("..")
            results.append((student, 0))
            break


        bitwiseRes = subprocess.run(['./testBitwiseFunctions'], capture_output=True)
        if bitwiseRes.returncode == 0:
            print("passed bitwise tests")
            studentScore += 20
        else:
            print("some bitwiseTests failed")
            decoded = bitwiseRes.stdout.decode("utf-8")
            print("results: %s" % decoded)
            passCount = decoded.count("passed")
            studentScore += 7 + passCount # 13 tests, so 7 points for compiling, and 1 for each passed one
            print("bitwise test score: %d", studentScore)

        makeRes = subprocess.run(['make', 'testFramework'], capture_output=True)
        if makeRes.returncode != 0:
            print("testFramework didn't compile: Skipping the tests" )
            print(makeRes.stdout)
            print(makeRes.stderr)
            os.chdir("..")
            results.append((student, studentScore))
            break

        print("test frmework built successfully")

        for i in range(1, 9):
            testRes = subprocess.run(['./testFramework','tests/test%d.rom' % i], capture_output=True)
            if testRes.returncode != 0:
                print("test %d failed" % i)
            else:
                diffRes = subprocess.run(['diff', '--color=auto', '-y', '--suppress-common-lines', 'tests/test%d.expected' % i, '-'],
                                         input=testRes.stdout, capture_output=True)
                if diffRes.returncode != 0:
                    print("test %d diff failed" % i)
                    print("diffs.stdout: %s" % diffRes.stdout)
                    print("diffs.stderr: %s" % diffRes.stderr)
                    diffs = diffRes.stdout.decode('utf-8').count("\n")
                    print("Num differnet lines: %s" % diffs)

                    thisScore = (max(expectedLines[i] - float(diffs), 0)/expectedLines[i])*testValues[i]
                    print("score on this test: %s" % thisScore)
                    studentScore += thisScore
                    
                else:
                    studentScore += testValues[i]
        print("%s scored %s" % (student, studentScore))
        os.chdir("..")
        results.append((student, studentScore))

print("******grades******")
for res in results:
    print("%s %f" % res)


        


        
