#include <stdio.h>
#include <math.h>
/// <summary>
/// Use for caculate sample average
/// Take elements from main function and return average
/// </summary>
/// <param name="S"></param>
/// <param name="size"></param>
/// <returns></returns>
double Average(double* S, int size);
/// <summary>
/// Use for caculate sample Variance
/// As you know this function's value always bigger than 0
/// Take elements and average from main function and return Variance
/// </summary>
/// <param name="S"></param>
/// <param name="x_bar"></param>
/// <param name="size"></param>
/// <returns></returns>
double Variance(double* S, double x_bar, int size);
/// <summary>
/// Use for caculate whether z or t value is higher than Significance Level
/// Also print that value in that function
/// I input often used significance level 0.1, 0.05, 0.01
/// *For Two Side Test, Don't use for one side test
/// </summary>
/// <param name="z"></param>
/// <param name="a"></param>
/// <param name="df"></param>
/// <param name="t"></param>
void SignificanceLevel(double z, double a,int df, int t);

int main(void)
{
	double array[100];
	int n, t = 0;
	double pop_mean, pop_variance, sample_mean, sample_variance, z, alpha= 0;

	printf("n's value: ");
	scanf("%d", &n);

	printf("pop mean's value: ");
	scanf("%lf", &pop_mean);

	printf("pop variance's value (if there is no pop variance, Type 0): ");
	scanf("%lf", &pop_variance);

	printf("Significance level (if there is no significance level, Type 0): ");
	scanf("%lf", &alpha);


	printf("Type sample's value: \n");

	for(int i = 0; i < n; i++)
		scanf("%lf", &array[i]);

	sample_mean = Average(array, n);
	sample_variance = Variance(array, sample_mean, n);

	//Student's t - distribution
	if(pop_variance == 0 && n < 30)
	{
		z = (sample_mean - pop_mean) / sqrt(sample_variance / n);
		t++;
	}
	//CLT && Standardized normal distribution
	else if(pop_variance == 0)
	{
		pop_variance = sample_variance;
		
		z = (sample_mean - pop_mean) / sqrt(pop_variance / n);
	}
	//Standardized normal distribution
	else
		z = (sample_mean - pop_mean) / sqrt(pop_variance / n);


	printf("Sample Mean : %.4lf \n", sample_mean);
	printf("Sample Variance : %.4lf \n", sample_variance);
	if(t >= 1)
	{
		//if Student's t - distribution
		printf("Degrees of freedom : %d\n", n - 1);
		printf("T");
	}
	else
		////if Standardized normal distribution
		printf("Z");

	printf(" - value : %.4lf \n", z);
	
	//to easy caculate
	if(z < 0) z = - z;

	SignificanceLevel(z, alpha, n - 1, t);

	return 0;
}

double Average(double* S, int size)
{
	double temp = 0;
	
	for(int i = 0; i < size; i++)
		temp += S[i];
	
	return temp / (double)size;
}

double Variance(double* S, double x_bar, int size)
{
	double temp = 0;

	for(int i = 0; i < size; i++)
		temp += pow(S[i] - x_bar, 2);

	return temp / (double)(size - 1);
}


void SignificanceLevel(double z, double a, int df, int t)
{
	//often used significance level 0.1, 0.05, 0.01
	//t-value's critical value[df][a]
	double critical_value_t[30][3] = {{6.314, 12.706, 63.656}, {2.920, 4.303, 9.925}, {2.353, 3.182, 5.841}, {2.132, 2.776, 4.604}, {2.015, 2.571, 4.032}, {1.943, 2.447, 3.707}, {1.895, 2.365, 3.499}, {1.860, 2.306, 3.355}, {1.833, 2.262, 3.250}, {1.812, 2.228, 3.169}, {1.796, 2.201, 3.106}, {1.782, 2.179, 3.055}, {1.771, 2.160, 3.012}, {1.761, 2.145, 2.977}, {1.753, 2.131, 2947}, {1.746, 2.120, 2.921}, {1.740, 2.110, 2.898}, {1.734, 2.101, 2.878}, {1.729, 2.093, 2.861}, {1.725, 2.086, 2.845}, {1.721, 2.080,2.831}, {1.717, 2.074, 2.819}, {1.714, 2.069, 2.807}, {1.711, 2.064, 2.797}, {1.708, 2.060, 2.787}, {1.706, 2.056, 2.779}, {1.703, 2.052, 2.771}, {1.701, 2.048, 2.763}, {1.699, 2.045, 2.756}, {1.645, 1.960, 2.576}};

	//z- value's critical value[a]
	double critical_value[3] = {1.645, 1.960, 2.575};

	if(t == 0)
	{
		//if Standardized normal distribution
		if(a == 0.1)
		{
			if(z < critical_value[0])
			{
				printf("It's in Acceptance Region\n");
				printf("Under %.1lf, H0 not reject(= H1 reject).\n", a);
			}
			else
			{
				printf("It's in Recjection Region\n");
				printf("Under %.2lf, H0 reject(= H1 not rejcet).\n", a);
			}
		}
		else if(a == 0.05)
		{
			if(z < critical_value[1])
			{
				printf("It's in Acceptance Region\n");
				printf("Under %.2lf, H0 not reject(= H1 reject).\n", a);
			}
			else
			{
				printf("It's in Recjection Region\n");
				printf("Under %.2lf, H0 reject(= H1 not rejcet).\n", a);
			}
		}
		else if(a == 0.01)
		{
			if(z < critical_value[2])
			{
				printf("It's in Acceptance Region\n");
				printf("Under %.2lf, H0 not reject(= H1 reject).\n", a);
			}
			else
			{
				printf("It's in Recjection Region\n");
				printf("Under %.2lf, H0 reject(= H1 not rejcet).\n", a);
			}
		}
		else if(a != 0)
			printf("Sorry, Will updata later\n");
	}
	else
	{
	//if Student's t distribution
		if(a == 0.1)
		{
			if(z < critical_value_t[df - 1][0])
			{
				printf("It's in Acceptance Region\n");
				printf("Under %.1lf, H0 not reject(= H1 reject).\n", a);
			}
			else
			{
				printf("It's in Recjection Region\n");
				printf("Under %.2lf, H0 reject(= H1 not rejcet).\n", a);
			}
		}
		else if(a == 0.05)
		{
			if(z < critical_value_t[df - 1][1])
			{
				printf("It's in Acceptance Region\n");
				printf("Under %.2lf, H0 not reject(= H1 reject).\n", a);
			}
			else
			{
				printf("It's in Recjection Region\n");
				printf("Under %.2lf, H0 reject(= H1 not rejcet).\n", a);
			}
		}
		else if(a == 0.01)
		{
			if(z < critical_value_t[df - 1][2])
			{
				printf("It's in Acceptance Region\n");
				printf("Under %.2lf, H0 not reject(= H1 reject).\n", a);
			}
			else
			{
				printf("It's in Recjection Region\n");
				printf("Under %.2lf, H0 reject(= H1 not rejcet).\n", a);
			}
		}
		else if(a != 0)
			printf("Sorry, Will updata later\n");
	}
}