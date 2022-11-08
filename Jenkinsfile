pipeline {
  agent any
  
  stages {
    stage ('Prepare') {
      steps {
        echo '==== Running prepare ===='
        sh 'git submodule init'
        sh 'git submodule update'
      }
    }

    stage ('Build') {
      steps {
        echo '==== Running build ===='
        sh 'mkdir build'
        sh 'cd build'
        sh 'cmake .. -DCMAKE_BUILD_TYPE=Release'
        sh 'make -j4'
      }
    }
  }
}