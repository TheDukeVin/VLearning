
data <- read.delim("/Users/kevindu/Desktop/Employment/Multiagent Snake Research/V_learning/Classic_V_Learn/exploit.out", sep=',', header = FALSE)

N = length(data[,1])

plot(1:N, data[,1], type='l', xlab="Millions of steps", ylab="Exploitability")
lines(1:N, data[,2], col='red')
lines(1:N, data[,3], col='blue')

legend(200, 0.35, legend=c("Agent 1", "Agent 2", "Agent 3"), 
       fill = c("black", "red","blue")
)

# nums <- integer(N)
# for(j in 1:N){
#   nums[j] = data[1,j]
# }
# 
# plot(1:N, nums, type='l')