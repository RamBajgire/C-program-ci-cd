pipeline {
    agent any

    stages {
        stage('build') {
            steps {
                sh '''pwd 
                make
                echo "20 30" | ./hello
                cat resul.txt
                '''
            }
        }
    }
}
