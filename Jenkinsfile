pipeline {
    agent any

    stages {
        stage('Hello') {
            steps {
                echo 'Hello World'
                sh 'ls'
            }
        }
        stage('parallel execution') {
            parallel {
                stage('A64X-paramneel') {
                    agent { label 'A64X' }  // Runs this on the A64X agent
                    steps {
                    sh '''pwd 
                    make
                    echo "20 30" | ./hello
                    cat result.txt
                    make clean
                    '''
                    }
                }
                stage('10.180.192.115') {
                    agent any // Runs this on the built-in Jenkins node
                    steps {
                        sh '''pwd 
                    make
                    echo "20 30" | ./hello
                    cat result.txt
                    make clean
                    '''
                    }
                }
            }
        }
    }
}
              
